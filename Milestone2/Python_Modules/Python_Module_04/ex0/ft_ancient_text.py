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
        archive: typing.IO[str] = open(argv[1])
        lido = archive.read()
        print("---")
        print(f"{lido}")
        print("---")
        archive.close()
        print(f"File '{argv[1]}' closed.")
    except OSError as error:
        print(f"Error opening file '{argv[1]}': {error}")


if __name__ == "__main__":

    if len(argv) != 2:
        args_verify()
    else:
        main()

#cat > ancient_fragment.txt << 'EOF'
#
#[FRAGMENT 001] Digital preservation protocols established 2087
#[FRAGMENT 002] Knowledge must survive the entropy wars
#[FRAGMENT 003] Every byte saved is a victory against oblivion
#EOF