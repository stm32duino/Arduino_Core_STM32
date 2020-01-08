import os
import re
import sys
import json
import subprocess
import argparse


# List
fqbn_list = []
arduino_cli = ""
arduino_cli_path = ""
stm32_url = "https://github.com/stm32duino/BoardManagerFiles/raw/master/STM32/package_stm_index.json"
arduino_platform = "STM32:stm32"

# Parser
parser = argparse.ArgumentParser(
    description="List STM32 core fqbn(s) using arduino-cli (Default list all)."
)

parser.add_argument(
    "-b", "--board", metavar="pattern", help="pattern to find one or more board(s) fqbn"
)
parser.add_argument(
    "-p", "--path", metavar="<arduino-cli path>", help="Path to the arduino-cli tool.",
)
args = parser.parse_args()


def check_config():
    try:
        output = subprocess.check_output(
            [arduino_cli, "core", "search", "stm32", "--additional-urls", stm32_url],
            stderr=subprocess.DEVNULL,
        )
        if arduino_platform not in output.decode("utf-8"):
            raise subprocess.CalledProcessError(1, "re")
    except subprocess.CalledProcessError:
        print(arduino_platform + " is not installed!")
        quit()


def get_fqbn_list():
    fqbn_list_tmp = []
    try:
        output = subprocess.check_output(
            [arduino_cli, "board", "listall", "--format", "json"],
            stderr=subprocess.DEVNULL,
        ).decode("utf-8")
        boards_list = json.loads(output)
        if boards_list is not None:
            for board in boards_list["boards"]:
                if arduino_platform in board["FQBN"]:
                    fqbn_list_tmp.append(board["FQBN"])
            if not len(fqbn_list_tmp):
                raise subprocess.CalledProcessError(2, "No fqbn")
        else:
            raise subprocess.CalledProcessError(1, "No fqbn")
    except subprocess.CalledProcessError:
        print("No fqbn found for " + arduino_platform + "!")
        quit()
    # For STM32 core, pnum is requested
    for fqbn in fqbn_list_tmp:
        try:
            output = subprocess.check_output(
                [arduino_cli, "board", "details", "--format", "json", fqbn],
                stderr=subprocess.DEVNULL,
            ).decode("utf-8")
            board_detail = json.loads(output)
            if board_detail is not None:
                if "config_options" not in board_detail:
                    raise subprocess.CalledProcessError(3, "No config_options")
                for option in board_detail["config_options"]:
                    if option["option"] == "pnum":
                        for value in option["values"]:
                            fqbn_list.append(fqbn + ":pnum=" + value["value"])
                    break
            else:
                raise subprocess.CalledProcessError(1, "No fqbn")
        except subprocess.CalledProcessError as e:
            print("No fqbn detail found for " + e.cmd + "!")
    if len(fqbn_list) == 0:
        print("No fqbn found for " + arduino_platform + "!")
        quit()


def main():
    global arduino_cli_path
    global arduino_cli
    if args.path:
        arduino_cli_path = args.path
        assert os.path.exists(
            arduino_cli_path
        ), "Path does not exist: '{}'. Please check the path!".format(
            arduino_cli_path
        )
    if sys.platform.startswith("win32"):
        arduino_cli = os.path.join(arduino_cli_path, "arduino-cli.exe")
    else:
        arduino_cli = os.path.join(arduino_cli_path, "arduino-cli")
    check_config()
    get_fqbn_list()

    if args.board:
        arg_board_pattern = re.compile(args.board, re.IGNORECASE)

    for fqbn in fqbn_list:
        if args.board:
            if arg_board_pattern.search(fqbn) is None:
                continue
        print(fqbn)


if __name__ == "__main__":
    main()
