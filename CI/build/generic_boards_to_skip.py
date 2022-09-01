import argparse
from pathlib import Path


script_path = Path(__file__).parent.resolve()
# Base path
core_path = script_path.parent.parent
variant_path = core_path / "variants"
boards_entry_filename = "boards_entry.txt"
output_filemane = script_path / "generic_boards_to_skip.json"

# Parser
parser = argparse.ArgumentParser(
    description="Generate list of generic boards to skip for ci core config"
)

parser.add_argument("-f", "--family", metavar="pattern", help="Family name to generate")

args = parser.parse_args()


def main():
    if args.family:
        filtered_family = args.family.upper()
    # Get mcu_family directories
    mcu_families = sorted(variant_path.glob("STM32*/"))
    boards_list = []
    # Parse boards from all
    for mcu_family in mcu_families:
        if args.family and filtered_family not in str(mcu_family):
            continue
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
    # Create file
    try:
        output_file = open(output_filemane, "w", newline="\n")
        for count, board in enumerate(sorted(boards_list), start=1):
            if count % 4 == 0:
                output_file.write(f'"{board}",\n')
            else:
                output_file.write(f'"{board}", ')
        output_file.close()
    except IOError:
        print(f"Failed to open {output_filemane}")
        exit(1)
    exit(0)


if __name__ == "__main__":
    main()
