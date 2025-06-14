from collections import ChainMap
import json
import logging
import math
import re
import jinja2 as jinja
from jinja2.nativetypes import NativeEnvironment
from esphome.const import CONF_JINJA, VALID_SUBSTITUTIONS_CHARACTERS
import esphome.config_validation as cv

TemplateError = jinja.TemplateError
TemplateSyntaxError = jinja.TemplateSyntaxError
TemplateRuntimeError = jinja.TemplateRuntimeError
UndefinedError = jinja.UndefinedError
Undefined = jinja.Undefined

CODEOWNERS = ["@jpeletier"]
_LOGGER = logging.getLogger(__name__)


def is_jinja_enabled(config):
    return CONF_JINJA in config


def validate_identifier(value):
    value = cv.string(value)
    if not value:
        raise cv.Invalid("Identifier name must not be empty")
    if value[0].isdigit():
        raise cv.Invalid("First character in an identifier cannot be a digit.")
    for char in value:
        if char not in VALID_SUBSTITUTIONS_CHARACTERS:
            raise cv.Invalid(
                f"Jinja identifier names must only consist of upper/lowercase characters, the underscore and numbers. The character '{char}' cannot be used"
            )
    return value


CONFIG_SCHEMA = cv.Schema(
    {
        cv.Optional("macros"): cv.ensure_schema(
            {
                validate_identifier: cv.Schema(
                    {
                        cv.Optional("parameters"): cv.ensure_schema(
                            cv.Schema({validate_identifier: object})
                        ),
                        cv.Required("return"): cv.string,
                    }
                )
            }
        ),
        cv.Optional("vars"): cv.ensure_schema(cv.Schema({validate_identifier: object})),
        cv.Optional("templates"): cv.ensure_list(cv.string_strict),
    }
)


DETECT_JINJA = r"(\$\{)"
detect_jinja_re = re.compile(
    r"<%.+?%>"  # Block form expression: <% ... %>
    r"|\$\{[^}]+\}",  # Braced form expression: ${ ... }
    flags=re.MULTILINE,
)


def has_jinja(st):
    return detect_jinja_re.search(st) is not None


class JinjaStr(str):
    """
    Wraps a string containing an unresolved Jinja expression,
    storing the variables visible to it when it failed to resolve.
    For example, an expression inside a package, `${ A * B }` may fail
    to resolve at package parsing time if `A` is a local package var
    but `B` is a substitution defined in the root yaml.
    Therefore, we store the value of `A` bound to the original string
    so we may be able to resolve `${ A * B }` later in the main substitutions pass.
    """

    __slots__ = ("vars",)

    def __new__(cls, value: str, vars=None):
        obj = super().__new__(cls, value)
        obj.vars = vars or {}
        return obj


class Jinja:
    """
    Wraps a Jinja environment
    """

    def __init__(self, config, context_vars):
        self.env = NativeEnvironment(
            trim_blocks=True,
            lstrip_blocks=True,
            block_start_string="<%",
            block_end_string="%>",
            line_comment_prefix="##",
            variable_start_string="${",
            variable_end_string="}",
            undefined=jinja.StrictUndefined,
        )
        self.env.add_extension("jinja2.ext.do")
        self.env.globals["math"] = math  # Inject entire math module
        self.context_vars = {**context_vars}

        if CONF_JINJA in config:
            with cv.prepend_path(CONF_JINJA):
                config[CONF_JINJA] = CONFIG_SCHEMA(config[CONF_JINJA])

            jinja_config = config[CONF_JINJA]
            if "vars" in jinja_config:
                self.load_vars(jinja_config["vars"])
            if "macros" in jinja_config:
                self.load_macros(jinja_config["macros"])
            if "templates" in jinja_config:
                self.load_templates(jinja_config["templates"])

        self.env.globals = {**self.env.globals, **self.context_vars}

    def parse_template(self, content, override_vars):
        local_env = self.env
        if len(override_vars) > 0:
            local_env = self.env.overlay()
            local_env.globals = ChainMap(override_vars, self.env.globals)
        template = local_env.from_string(content)
        for symbol_name in dir(template.module):
            if symbol_name.startswith("_"):
                continue
            self.env.globals[symbol_name] = getattr(template.module, symbol_name)

    def load_vars(self, vars):
        """
        Adds variables only visible to Jinja. Note that substitutions
        have precedence and will override these
        """
        for var_name, value in vars.items():
            if var_name not in self.context_vars:
                self.context_vars[var_name] = value

    def capture_vars(self, st):
        vars = self.context_vars
        if isinstance(st, JinjaStr):
            vars = st.vars = {**self.context_vars, **st.vars}
        return JinjaStr(st, vars)

    def load_macros(self, macros):
        """
        Creates Jinja macros out of a simplified yaml syntax
        """
        for name, macro in macros.items():
            parameters = ", ".join(
                [f"{k}={json.dumps(v)}" for k, v in macro["parameters"].items()]
            )
            return_value = macro["return"]
            macro["return"] = return_value = self.capture_vars(return_value)

            self.parse_template(
                f"<% macro {name}({parameters}) %>${{{return_value}}}<% endmacro %>",
                return_value.vars,
            )

    def load_templates(self, templates):
        """
        Adds Jinja templates to the environment
        """
        for i, content in enumerate(templates):
            templates[i] = content = self.capture_vars(content)
            self.parse_template(content, content.vars)

    def expand(self, value):
        """
        Evaluates a jinja expression.
        Returns the resulting processed string if all values could be resolved
        Otherwise, it returns a tagged (JinjaStr) string that captures variables
        in scope, like a closure.
        """
        template = self.env.from_string(value)
        result = None
        override_vars = {}
        if isinstance(value, JinjaStr):
            # If `value` is already a JinjaStr, it means we are trying to evaluate it again
            # in a parent pass.
            # Hopefully, all required variables are visible now.
            override_vars = value.vars
        try:
            result = template.render(override_vars)
            if isinstance(result, Undefined):
                print("" + result)  # force a UndefinedError exception
        except UndefinedError as err:
            # `value` contains a Jinja expression that refers to a variable that is undefined
            # in this scope. Perhaps it refers to a root substitution that is not visible yet.
            # Therefore, return `value` as a JinjaStr, which contains the variables
            # that are actually visible to it at this point to postpone evaluation.
            return JinjaStr(value, {**self.context_vars, **override_vars}), err

        return result, None
