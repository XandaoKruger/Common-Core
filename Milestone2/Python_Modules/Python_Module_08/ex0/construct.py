#!/usr/bin/env python3

import sys
import os
import site


# Verificador se está ou não dentro do venv
def in_virtual_env() -> bool:
    return sys.base_prefix != sys.prefix


def report_inside() -> None:
    '''Decisão de usar o sys.prefix, é o próprio interpretador reportando por
    si mesmo, é fonte primária, já o os.enviren.get("VIRTUAL_ENV") pode puxar
    qualquer informação de algum venv antigo que não foi encerrado, um script
    que pode estar ausente ou desatualizado, é fonte secundária. No final
    fazem o mesmo, mas estruturalmente sys.prefix é mais confiável.'''

    print("\n\033[32mMATRIX STATUS\033[m: Welcome to the construct\n")

    print(f"\033[34mCurrent Python\033[m: {sys.executable}")
    print(f"\033[34mVirtual Environment\033[m: {os.path.basename(sys.prefix)}")
    print(f"\033[34mEnvironment Path\033[m: {sys.prefix}")

    print(
        "\n\033[32mSUCCESS\033[m: You're in an isolated enviroment!\
\nSafe to install packages whithout affecting\
\nthe global system.\n"
        )

    print(
        f"\033[34mPackage installation path\033[m:\
\n{site.getsitepackages()[0]}"
        )


def report_outside() -> None:

    print("\n\033[32mMATRIX STATUS\033[m: You're still plugged in\n")

    print(f"\033[34mCurrent Python\033[m: {sys.executable}")
    print("\033[34mVirtual Environment\033[m: None detected")

    print("\n\033[31mWARNING\033[m: You're in the global enviroment!\n\
The machines can see everything you install.\n")

    print("\033[36mTo enter the construct, run\033[m:")
    print("\033[33mpython -m venv matrix_env\033[m")
    print("source matrix_env/bin/activate # On Unix")
    print("matrix_env\\scripts\\activate # On Windows")

    print("\nThen run this program again.\n")


def main() -> None:
    if in_virtual_env():
        report_inside()
    else:
        report_outside()


if __name__ == "__main__":
    main()
