#!/usr/bin/env python3

from __future__ import annotations
import importlib
from typing import Any
try:
    import numpy as np
    import pandas as pd
    import matplotlib.pyplot as plt
except ImportError:
    np = pd = plt = None  # type: ignore[assignment]

nomes = ["pandas", "numpy", "matplotlib", "requests"]


def check_imports() -> dict[str, Any]:
    result = {}

    for nome in nomes:
        try:
            modulo = importlib.import_module(nome)
            result[nome] = {"ok": True, "version": modulo.__version__}
        except ImportError:
            result[nome] = {"ok": False, "version": None}
    return result


def built_data() -> np.ndarray:
    shuffle = np.random.uniform(0, 600, 1000)
    return shuffle


def data_process(data: np.ndarray) -> pd.DataFrame:
    dataframe = pd.DataFrame({"matrix_signal": data})
    return dataframe


def built_grafic(data: np.ndarray) -> None:
    plt.hist(data)
    plt.savefig("matrix_analysis.png")


def main() -> None:
    imports = check_imports()

    # Loop para cada import com os valores dentro do dict
    for nome, info in imports.items():

        status = (
            "\033[32m[OK]\033[m"
            if info["ok"]
            else "\033[31m[MISSING]\033[m"
        )

        # Printa o status, com o nome, e se tiver, printa versão.
        print(f"{status} {nome} {info['version'] or ''}")

    # Varre o dict inteiro, caso uma for false, entra e executa
    if any(not info["ok"] for info in imports.values()):
        return

    print("\033[33m\nAnalyzing Matrix data...")
    dados = built_data()

    print("Processing 1000 data points...\033[m")
    data_process(dados)

    print("\033[34mGenerate visualization...\033[m\n")

    built_grafic(dados)

    print("\033[32mAnalysis complete!")
    print("Results saved to\033[m: matrix_analysis.png")


if __name__ == "__main__":
    print("\033[33mLOADING STATUS\033[m: Loading programs..\n")

    print("Checking dependencies:")

    main()
