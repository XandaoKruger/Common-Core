#!/usr/bin/env python3
from math import sqrt


def get_player_pos() -> tuple[float, ...]:
    while True:
        cord = input("Enter new coordinates as float in format 'x,y,z': ")
        partes = cord.split(",")

        # len() hardcoded porque nao esta liberado
        leng = 0
        for _ in partes:
            leng += 1

        # Verificacao de argumentos
        if leng != 3:
            print("Invalid syntax")
            continue

        # Iniciando a lista e o bool da valvula de escape
        convert: tuple[float, ...] = ()
        erros = False

        for parte in partes:
            try:

                # Conversao p/ float e adicionar a lista
                val_float = float(parte)
                convert += (val_float,)
            except ValueError as e:
                print(f"Error on parameter '{parte}': {e}")
                erros = True
                break

        # Valvula de escape, sai do while antes de executar o return
        if erros:
            continue

        return convert


if __name__ == "__main__":
    print("=== Game Coordinate System ===")

    print("Get a first set of coordinates")
    x1 = get_player_pos()

    print(f"Got a first tuple: {x1}")
    print(f"It includes: X={x1[0]}, Y={x1[1]}, Z={x1[2]}")

    centro1 = sqrt(x1[0]**2 + x1[1]**2 + x1[2]**2)

    print(f"Distance to center: {round(centro1, 4)}")

    print()

    print("Get a second set of coordinates")
    x2 = get_player_pos()

    # centro2 = sqrt(x2[0]**2 + x2[1]**2 + x2[2]**2)

    dif = sqrt((x2[0] - x1[0])**2 + (x2[1] - x1[1])**2 + (x2[2] - x1[2])**2)
    print(f"Distance between the 2 sets of coordinates: {dif:.4f}")
