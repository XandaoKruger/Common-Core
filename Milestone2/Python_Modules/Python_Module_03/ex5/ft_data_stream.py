#!/usr/bin/env python3

import typing
import random

PLAYERS = ["Bob", "Alice", "Dylan", "Charlie"]

ACTIONS = [
    "run", "eat", "sleep", "grab", "climb", "move", "swim", "use", "release"
]


def gen_event() -> typing.Generator[tuple[str, str], None, None]:

    rand_player = random.choice(PLAYERS)
    rand_action = random.choice(ACTIONS)

    # "Retorna" sem matar o processo a tupla com a ordem player -> action
    yield (rand_player, rand_action)


def consume_event()

if __name__ == "__main__":

    for i in range(1000):

        # next para passar ao proximo yield a cada iteracao
        gen = next(gen_event())
        print(f"Event {i}: Player {gen[0]} did action {gen[1]}")

    # Criando a lista de 10
    lista_10: list[str] = []
    for _ in range (10):
        lista_10.append(gen)

    print(f"\nBuilt list of 10 events: {lista_10}\n")