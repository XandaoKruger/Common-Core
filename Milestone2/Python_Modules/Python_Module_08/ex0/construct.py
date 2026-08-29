#!/usr/bin/env python3

import sys
import os
import site


# Verificador se está ou não dentro do venv
def in_virtual_env() -> bool:
    return sys.base_prefix != sys.prefix


def report_inside() -> None:
    '''Decisão de usar o sys.prefix, é o próprio interpretador reportando por si
    mesmo, é fonte primária, já o os.enviren.get("VIRTUAL_ENV") pode puxar
    qualquer informação de algum venv antigo que não foi encerrado, um script
    que pode estar ausente ou desatualizado, é fonte secundária. No final
    fazem o mesmo, mas estruturalmente sys.prefix é mais confiável.'''

    print(f"Current Python: {sys.executable}")
    print(f"Environment Path: {sys.prefix}")
    print(f"Virtual Environment: {os.path.basename(sys.prefix)}")
    print(f"Package installation path:\n{site.getsitepackages()[0]}")

def report_outside() -> None:
    print(f"Current Python: {sys.executable}")

os.path.basename
def main() -> None:
    if in_virtual_env():
        report_inside()
    else:
        report_outside()


if __name__ == "__main__":
    main()
