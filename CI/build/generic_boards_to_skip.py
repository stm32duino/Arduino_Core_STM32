import argparse
import json
from pathlib import Path


script_path = Path(__file__).parent.resolve()
# Base path
core_path = script_path.parent.parent
variant_path = core_path / "variants"
boards_entry_filename = "boards_entry.txt"
# Config files
conf_path = script_path / "conf"
cores_file = conf_path / "cores_config.json"
ci_file = conf_path / "cores_config_ci.json"

# Parser
parser = argparse.ArgumentParser(
    description="Generate list of generic boards to skip for ci core config"
)


def update_config(config_file, boards_list):
    if not config_file.is_file():
        print(f"{config_file} not found!")
        exit(1)
    try:
        config = open(config_file, "r")
        json_data = json.load(config)
        config.close()
        # Update the values for generic boards
        # First search correct value
        core_index = -1
        sketch_index = -1
        for index, core in enumerate(json_data["cores"]):
            if core["architecture"] == "stm32":
                core_index = index
                for index2, sketch in enumerate(core["sketches"]):
                    if sketch["pattern"] == "^.*$":
                        sketch_index = index2
        old_boards_list = json_data["cores"][core_index]["sketches"][sketch_index][
            "boards"
        ]
        old_boards_list = [x for x in old_boards_list if not x.startswith("GENERIC_")]
        new_boards_list = old_boards_list + boards_list
        new_boards_list.sort()
        json_data["cores"][core_index]["sketches"][index]["boards"] = new_boards_list
        config = open(config_file, "w")
        config.write(json.dumps(json_data, indent=2))
        config.close()
    except IOError:
        print(f"Failed to open {config_file}!")


def main():
    # Get mcu_family directories
    mcu_families = sorted(variant_path.glob("STM32*/"))
    boards_list = []
    # Parse boards from all
    for mcu_family in mcu_families:
        # Search all directory with ldscript.ld
        variants_list = sorted(mcu_family.glob("**/ldscript.ld"))
        for variant in variants_list:
            # Opend boards_entry.txt and extract build.board
            with open(variant.parent / "boards_entry.txt") as myfile:
                for line in myfile:
                    if "build.board" in line:
                        boards_list.append(line.partition("=")[-1].strip())
            # Remove last board of the boards_entry to not skip it
            boards_list.pop()
    boards_list.sort()

    # Update each config files
    update_config(ci_file, boards_list)
    update_config(cores_file, boards_list)

    exit(0)


if __name__ == "__main__":
    main()
