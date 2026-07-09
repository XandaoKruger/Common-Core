#!/usr/bin/env python3
import sys
import typing


def args_verify() -> None:

    print("Usage: ft_ancient_text.py <file>")
    return


def main() -> None:
    arg_um = sys.argv[1]
    check_flag = False

    print("=== Cyber Archives Recovery ===")
    print(f"Accessing file: '{sys.argv[1]}'")

    try:
        archive: typing.IO[str] = open(arg_um)
        lido = archive.read()
        print(f"---\n\n{lido}\n---")
        archive.close()
        print(f"File '{sys.argv[1]}' closed.")

        cortada = lido.splitlines()
        editada = [linha + "#" for linha in cortada]
        edit_lines = "\n".join(editada)
        print(f"\nTransform data:\n---\n\n{edit_lines}\n\n---")

        sys.stdout.write("Enter new file name (or empty): ")
        sys.stdout.flush()
        new_name = sys.stdin.readline().strip()
        if not new_name:
            print("Not saving data.")
        else:
            print(f"Saving data to '{new_name}'")
            arg_um = new_name
            check_flag = True
            saving_point = open(arg_um, "w")
            saving_point.write(edit_lines)
            saving_point.close()
            print(f"Data saved in file '{new_name}'.")

    except OSError as error:
        sys.stderr.write(f"[STDERR] Error opening file '{arg_um}': {error}\n")
        if check_flag:
            print("Data not saved.")


if __name__ == "__main__":

    if len(sys.argv) != 2:
        args_verify()
    else:
        main()

# cat > ancient_fragment.txt << 'EOF'
# [FRAGMENT 001] Digital preservation protocols established 2087
# [FRAGMENT 002] Knowledge must survive the entropy wars
# [FRAGMENT 003] Every byte saved is a victory against oblivion
# EOF
