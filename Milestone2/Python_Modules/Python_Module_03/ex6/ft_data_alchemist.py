#!/usr/bin/env python3

import random

PLAYERS = ["Alexandre", "Ana", "clara", "BRIAN", "ethan", "Mia", "baker"]

only_cap = [nome for nome in PLAYERS if nome.istitle()]

cap = [nome.capitalize() for nome in PLAYERS]

scores = {nome: random.randint(0, 1000) for nome in cap}

avg = sum(scores[nome] for nome in scores) / len(scores)

high = {nome: scores[nome] for nome in scores if scores[nome] > avg}


if __name__ == "__main__":
    print("=== Game Data Alchemist ===\n")

    print(f"Initial list of players: {PLAYERS}\n")

    print(f"New list with all names capitalized: {cap}\n")

    print(f"New list of capitalized names only: {only_cap}\n")

    print(f"Score dict: {scores}\n")

    print(f"Score average is {avg:.2f}\n")

    print(f"High scores: {high}")
