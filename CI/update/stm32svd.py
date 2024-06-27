import json
import sys
from pathlib import Path

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils import copyFile, copyFolder, createFolder, deleteFolder
from utils import defaultConfig, genSTM32List

stm32_list = []  # series
root_path = script_path.parent.parent.resolve()
hal_path = root_path / "system" / "Drivers"
cubeclt_path = Path("")
cubeclt_svd_path = Path("")
stm32_svd_repo = Path("")
stm32_svd_dir = Path("")


def checkConfig():
    global cubeclt_path
    global cubeclt_svd_path
    global stm32_svd_repo
    global stm32_svd_dir
    config_file_path = script_path / "update_config.json"
    if config_file_path.is_file():
        try:
            config_file = open(config_file_path, "r")
            path_config = json.load(config_file)
            config_file.close()

            if "STM32CUBECLT_PATH" not in path_config:
                path_config["STM32CUBECLT_PATH"] = str(
                    "Path to STM32CubeCLT installation directory"
                )
                defaultConfig(config_file_path, path_config)
            else:
                cubeclt_path = Path(path_config["STM32CUBECLT_PATH"])
            if not cubeclt_path.is_dir():
                print(f"{cubeclt_path} does not exist!")
                exit(1)
            else:
                cubeclt_svd_path = cubeclt_path / "STMicroelectronics_CMSIS_SVD"
                if not cubeclt_svd_path.is_dir():
                    print(f"{cubeclt_svd_path} does not exist!")
                    exit(1)
            if "STM32_SVD_PATH" not in path_config:
                path_config["STM32_SVD_PATH"] = str("Path to stm32_svd repository")
                defaultConfig(config_file_path, path_config)
            else:
                stm32_svd_repo = Path(path_config["STM32_SVD_PATH"])
            if not stm32_svd_repo.is_dir():
                print(f"{stm32_svd_repo} does not exist!")
                exit(1)
            else:
                stm32_svd_dir = stm32_svd_repo / "svd"
        except IOError:
            print(f"Failed to open {config_file}!")
    else:
        defaultConfig(
            config_file_path,
            {"STM32CUBECLT_PATH": "Path to STM32CubeCLT installation directory"},
        )


def main():
    global stm32_list
    # check config have to be done first
    checkConfig()
    stm32_list = genSTM32List(hal_path, None)
    # Reverse order to get WBA before WB to ease svd sorting
    stm32_list.sort(reverse=True)
    # Clean up core svd folder
    deleteFolder(stm32_svd_dir)
    createFolder(stm32_svd_dir)
    # Update the Core folder
    copyFolder(cubeclt_svd_path / "Core", stm32_svd_dir / "Core")
    # Update the license
    copyFile(cubeclt_svd_path / "about.html", stm32_svd_dir)
    # Copy the version
    copyFile(cubeclt_path / ".version", stm32_svd_dir / "STM32CubeCLT.version")
    # Create all directories
    for serie in stm32_list:
        createFolder(stm32_svd_dir / f"STM32{serie}xx")
    # Get all xml files
    svd_list = sorted(cubeclt_svd_path.glob("STM32*.svd"))

    # Copy all svd files per series
    for svd_file in svd_list:
        svd_name = svd_file.name
        for serie in stm32_list:
            if svd_name.find(f"STM32{serie}") != -1:
                copyFile(svd_file, stm32_svd_dir / f"STM32{serie}xx")
                break


if __name__ == "__main__":
    main()
