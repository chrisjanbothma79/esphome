import json
from unittest.mock import Mock, patch

from esphome import vscode


def _run_repl_test(input_data):
    """Reusable test function for different input scenarios."""
    input_data.append(_exit())
    with (
        patch("builtins.input", side_effect=input_data),
        patch("sys.stdout") as mock_stdout,
    ):
        args = Mock([])
        args.ace = False
        args.substitution = None
        vscode.read_config(args)

        # Capture printed output
        full_output = "".join(call[0][0] for call in mock_stdout.write.call_args_list)
        return full_output.strip().split("\n")


def _validate(file: str):
    return json.dumps({"type": "validate", "file": file})


def _file_response(data: str):
    return json.dumps({"type": "file_response", "content": data})


def _exit():
    return json.dumps({"type": "exit"})


RESULT_NO_ERROR = '{"type": "result", "yaml_errors": [], "validation_errors": []}'


def test_multi_file():
    output_lines = _run_repl_test(
        [
            _validate("c:/dir_path/x.yaml"),
            # read_file x.yaml
            _file_response("""esphome:
  name: test1
esp8266:
  board: !secret my_secret_board
"""),
            # read_file secrets.yaml
            _file_response("""my_secret_board: esp1f"""),
        ]
    )

    expected_lines = [
        '{"type": "read_file", "path": "c:/dir_path/x.yaml"}',
        '{"type": "read_file", "path": "c:/dir_path\\\\secrets.yaml"}',
        RESULT_NO_ERROR,
    ]

    assert output_lines == expected_lines


def test_shows_correct_range_error():
    output_lines = _run_repl_test(
        [
            _validate("c:/dir_path/x.yaml"),
            # read_file x.yaml
            _file_response("""esphome:
  name: test1
esp8266:
  broad: !secret my_secret_board        # typo here
"""),
            # read_file secrets.yaml
            _file_response("""my_secret_board: esp1f"""),
        ]
    )

    assert len(output_lines) == 3
    error = json.loads(output_lines[2])
    validation_error = error["validation_errors"][0]
    assert validation_error["message"].startswith("[broad] is an invalid option for")
    range = validation_error["range"]
    assert range["document"] == "c:/dir_path/x.yaml"
    assert range["start_line"] == 3
    assert range["start_col"] == 2
    assert range["end_line"] == 3
    assert range["end_col"] == 7


def test_shows_correct_loaded_file_error():
    output_lines = _run_repl_test(
        [
            _validate("c:/dir_path/x.yaml"),
            # read_file x.yaml
            _file_response("""esphome:
  name: test1

packages:
  board: !include .pkg.esp8266.yaml
"""),
            # read_file .pkg.esp8266.yaml
            _file_response("""esp8266:
  broad: esp1f # typo here
"""),
        ]
    )

    assert len(output_lines) == 3
    error = json.loads(output_lines[2])
    validation_error = error["validation_errors"][0]
    assert validation_error["message"].startswith("[broad] is an invalid option for")
    range = validation_error["range"]
    assert range["document"] == "c:/dir_path\\.pkg.esp8266.yaml"
    assert range["start_line"] == 1
    assert range["start_col"] == 2
    assert range["end_line"] == 1
    assert range["end_col"] == 7
