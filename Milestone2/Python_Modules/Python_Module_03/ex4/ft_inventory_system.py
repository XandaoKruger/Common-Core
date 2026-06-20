#!/usr/bin/env python3
import sys


def inventory_loot() -> None:

    inventario: dict[str, int] = {} 

    for arg in sys.argv[1:]:

        # Split dos argumentos via :
        partes = arg.split(":")

        # Tratamento de argumento inválido, mais "continue" para passar ao 
        # próximo argumento, sem executar o resto.
        if len(partes) != 2:
            print(f"Error - Invalid parameter '{arg}'")
            continue

        # Try para converter str para int, se não, erro.
        try:
            quant = int(partes[1])
        except ValueError as e:
            print(f"Quantity error for '{partes[0]}': {e}")
            continue

        if partes[0] in inventario:
            print(f"Redundant item '{partes[0]}' - discarding")
            continue

        print(partes)

if __name__ == "__main__":
    print("=== Inventory System Analysis ===") 
    inventory_loot()