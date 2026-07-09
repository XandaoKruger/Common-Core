#!/usr/bin/env python3
from sys import argv
import typing


def args_verify() -> None:

    print("Usage: ft_ancient_text.py <file>")
    return


def main() -> None:

    print("=== Cyber Archives Recovery ===")
    print(f"Accessing file: '{argv[1]}'")

    try:

        # Abre e lê o arquivo
        archive: typing.IO[str] = open(argv[1])
        lido = archive.read()
        print(f"---\n\n{lido}\n---")
        archive.close()
        print(f"File '{argv[1]}' closed.")

        # Separa, adiciona # e junta novamente
        cortada = lido.splitlines()
        editada = [linha + "#" for linha in cortada]
        edit_lines = "\n".join(editada)
        print(f"\nTransform data:\n---\n\n{edit_lines}\n\n---")

        # Recebe o input do nome, vê se existe, abre, edita/salva e fecha
        new_name = input("Enter new file name (or empty): ")
        if not new_name:
            print("Not saving data.")
        else:
            print(f"Saving data to '{new_name}'")
            saving_point = open(new_name, "w")
            saving_point.write(edit_lines)
            saving_point.close()
            print(f"Data saved in file '{new_name}'.")

    except OSError as error:
        print(f"Error opening file '{argv[1]}': {error}")


if __name__ == "__main__":

    if len(argv) != 2:
        args_verify()
    else:
        main()

# cat > ancient_fragment.txt << 'EOF'
# [FRAGMENT 001] Digital preservation protocols established 2087
# [FRAGMENT 002] Knowledge must survive the entropy wars
# [FRAGMENT 003] Every byte saved is a victory against oblivion
# EOF
