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

        inventario[partes[0]] = quant

    print(f"Got inventory: {inventario}")

    # Mostra apenas a lista de items, sem quantidade.
    item_list = list(inventario.keys())

    # Mostra a soma da quantidade total de itens.
    total = sum(inventario.values())

    print(f"Item list: {item_list}")
    print(f"Total quantity of the {len(item_list)} items: {total}")

    # Porcentagem da representatividade de cada item no inventario.
    for item in inventario:
        value = inventario[item] / total * 100
        print(f"Item {item} represents {value:.1f}%")

    maior_item = None
    maior_quant = -1

    menor_item = None
    # Para iniciar de modo seguro, sem chutar um valor, usar a mecanica nativa
    #  de infinito -> "float('inf')" 
    menor_quant = float('inf')

    for item_ in inventario:
        if inventario[item_] > maior_quant:
            # Identifica o item.
            maior_item = item_
            # Identifica o valor
            maior_quant = inventario[item_]

        if inventario[item_] < menor_quant:
            menor_item = item_
            menor_quant = inventario[item_]

    print(f"Item most abundant: {maior_item} with quantity {maior_quant}")
    print(f"Item least abundant: {menor_item} with quantity {menor_quant}")

    inventario.update({"magic_item": 1})
    print(f"Update inventory {inventario}")


if __name__ == "__main__":
    print("=== Inventory System Analysis ===") 
    inventory_loot()
