#!/usr/bin/env python3
import math

def get_player_pos() -> tuple[float, float, float]:
    while True:
        cord = input("Enter new coordinates as float in format 'x,y,z': ")
        partes = cord.split(",")
        if len(partes) != 3:
            print(f"Invalid syntax")
            continue

        try:
            x = float(partes[0])
            y = float(partes[1])
            z = float(partes[2])
            return (x, y, z)
        except ValueError as e:
            print(f"Error on parameter '...': {e}")
            continue
