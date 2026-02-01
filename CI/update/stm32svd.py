import json
import sys
from collections import OrderedDict
from pathlib import Path
from xml.dom.minidom import parse

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils import copyFile, copyFolder, createFolder, deleteFolder
from utils import defaultConfig, genSTM32Dict

stm32_list = []  # series
stm32_dict = OrderedDict()  # key: serie, value: nx
svd_dict = {}  # 'svd file': 'name'
root_path = script_path.parent.parent.resolve()
hal_path = root_path / "system" / "Drivers"
cubeclt_path = Path("")
cubeclt_mcu_path = Path()
cubeclt_svd_path = Path("")
stm32_svd_repo = Path("")
stm32_svd_dir = Path("")


def checkConfig():
    global cubeclt_path
    global cubeclt_mcu_path
    global cubeclt_svd_path
    global stm32_svd_repo
    global stm32_svd_dir
    config_file_path = script_path / "update_config.json"
    if config_file_path.is_file():
        try:
            with open(config_file_path, "r") as config_file:
                path_config = json.load(config_file)

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
                cubeclt_mcu_path = cubeclt_path / "STM32target-mcu"
                if not cubeclt_mcu_path.is_dir():
                    print(f"{cubeclt_mcu_path} does not exist!")
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


def parse_stm32targets(stm32targets_file: Path):
    global svd_dict

    xml_stm32targets = parse(str(stm32targets_file))
    mcu_nodes = xml_stm32targets.getElementsByTagName("mcu")
    for mcu_node in mcu_nodes:
        parent_node_name = mcu_node.getElementsByTagName("parent")[0].firstChild.data
        mcu_node_name = mcu_node.getElementsByTagName("name")[0].firstChild.data
        cpus_node_name = mcu_node.getElementsByTagName("cpus")
        cpu_node_name = cpus_node_name[0].getElementsByTagName("cpu")
        svd_node = cpu_node_name[0].getElementsByTagName("svd")
        svd_file = svd_node[0].getElementsByTagName("name")[0].firstChild.data
        serie = (
            parent_node_name.upper()
            .removeprefix("STM32")
            .removesuffix("SINGLE")
            .removesuffix("DUAL")
        )
        if serie == "L4PLUS":
            serie = "L4"
        else:
            if mcu_node_name.startswith("STM32H7R") or mcu_node_name.startswith(
                "STM32H7S"
            ):
                serie = "H7RS"
        svd_dict[svd_file] = serie
        # Check if a second cpu is defined
        if cpu_node_name.length > 1:
            svd_node = cpu_node_name[1].getElementsByTagName("svd")
            svd_file = svd_node[0].getElementsByTagName("name")[0].firstChild.data
            serie = parent_node_name.upper().removeprefix("STM32").removesuffix("DUAL")
            svd_dict[svd_file] = serie
    xml_stm32targets.unlink()


def main():
    global stm32_dict
    global stm32_list
    # Check config have to be done first
    checkConfig()
    # Get list of STM32 series from HAL driver directory
    stm32_dict = genSTM32Dict(hal_path, None)
    stm32_list = sorted(list(stm32_dict.keys()))
    # Parse STM32Targets.xml to get list of STM32 series and svd file
    # one per Cube reference
    stm32targets_file = cubeclt_mcu_path / "stm32targets.xml"
    if stm32targets_file.is_file():
        parse_stm32targets(stm32targets_file)
    else:
        print(f"{stm32targets_file} does not exits!")
        exit(1)
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
        nx = stm32_dict[serie]
        createFolder(stm32_svd_dir / f"STM32{serie}{nx}")
    # Get all svd files
    svd_list = sorted(cubeclt_svd_path.glob("STM32*.svd"))

    # Copy all svd files per supported series
    for svd_file in svd_list:
        svd_name = svd_file.name
        if svd_name in svd_dict:
            if svd_dict[svd_name] in stm32_list:
                copyFile(
                    svd_file,
                    stm32_svd_dir
                    / f"STM32{svd_dict[svd_name]}{stm32_dict[svd_dict[svd_name]]}",
                )
        else:
            # File not copied as not referenced in stm32targets.xml
            if svd_name.startswith("STM32GBK"):
                copyFile(svd_file, stm32_svd_dir / "STM32G4xx")
            else:
                for serie in stm32_list:
                    nx = stm32_dict[serie]
                    if svd_name.startswith(f"STM32{serie}"):
                        copyFile(svd_file, stm32_svd_dir / f"STM32{serie}{nx}")
                        break
                else:
                    print(f"File {svd_name} not copied.")

    # Check if created folder is empty and delete it
    for serie in stm32_list:
        nx = stm32_dict[serie]
        serie_dir = stm32_svd_dir / f"STM32{serie}{nx}"
        if not any(serie_dir.glob("*")):
            print(f"Folder {serie_dir} is empty.")
            serie_dir.rmdir()


if __name__ == "__main__":
    main()
