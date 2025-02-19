import os
from pathlib import Path
import shutil

from esphome.core import _LOGGER, CORE

from . import cmake


class SDKConfig:
    def __init__(self, path: Path):
        self.path = path
        self.map = {}
        if path.exists():
            for line in path.read_text().split("\n"):
                if "=" not in line:
                    continue
                key, value = line.split("=")
                self.map[key] = value
        else:
            path.touch()
            self.map = {}

    def get_content(self) -> str:
        return "\n".join([f"{k}={v}" for k, v in self.map.items()])

    def write(self):
        self.path.write_text(self.get_content())

    def __getitem__(self, key: str) -> str:
        return self.map[key]

    def __setitem__(self, key: str, value: str):
        self.map[key] = value

    def __delitem__(self, key: str):
        del self.map[key]


class Formatter(cmake.Formatter):
    def include_espidf_project(self) -> str:
        return "include($ENV{IDF_PATH}/tools/cmake/project.cmake)"

    def compile_definitions(self, definitions: list[str]) -> str:
        return "\n".join(
            [
                f'idf_build_set_property(COMPILE_DEFINITIONS "{d}" APPEND)'
                for d in definitions
            ]
        )

    def compile_options(self, flags: list[str]) -> str:
        return "\n".join(
            [f'idf_build_set_property(COMPILE_OPTIONS "{f}" APPEND)' for f in flags]
        )


class Generator(cmake.Generator):
    def get_content(self, f: Formatter = Formatter()) -> str:
        # CORE.add_platformio_option(
        #    "lib_deps",
        #    [x.as_lib_dep for x in CORE.platformio_libraries] + ["${common.lib_deps}"],
        # )
        # Sort to avoid changing build flags order
        content = [
            f.include_espidf_project(),
            f.project(CORE.name),
            f.compile_definitions(cmake.get_compile_defines()),
            f.compile_options(cmake.get_compile_options()),
        ]

        return "\n\n".join(content) + "\n"

    def write_main_component_cmakelists(self):
        path = Path(CORE.relative_src_path("CMakeLists.txt"))
        if not path.exists():
            path.write_text(
                "\n".join(
                    [
                        "file(GLOB_RECURSE ESP_SRCS *.cpp)",
                        'idf_component_register(SRCS ${ESP_SRCS} INCLUDE_DIRS ".")',
                    ]
                )
            )

    def write_project(self):
        super().write_project()
        shutil.copyfile(
            CORE.relative_build_path(f"sdkconfig.{CORE.name}"),
            CORE.relative_build_path("sdkconfig"),
        )
        self.write_main_component_cmakelists()
        # self.write_sdkconfig()


class Builder:
    def build(self):
        # get IDF_PATH environment variable
        try:
            # IDF_PATH =
            Path(os.environ["IDF_PATH"])
        except KeyError:
            _LOGGER.error(
                "$IDF_PATH environment variable not set, cannot build automatically. "
                "You can either set IDF_PATH and re-run this command, or change to the build directory "
                "and manually execute 'idf.py build' from an ESP-IDF terminal."
            )
            return

        # os.chdir(CORE.build_path)
        # process = subprocess.Popen(["cmake", "-B", "build", "-G", "Ninja"], shell=False)
        # process.communicate()
        # process.wait()
