#!/usr/bin/env python3

import typing
import random

PLAYERS = ["Bob", "Alice", "Dylan", "Charlie"]

ACTIONS = [
    "run", "eat", "sleep", "grab", "climb", "move", "swim", "use", "release"
]


def gen_event() -> typing.Generator[tuple[str, str], None, None]:

    while True:
        rand_player = random.choice(PLAYERS)
        rand_action = random.choice(ACTIONS)

        # "Retorna" sem matar o processo a tupla com a ordem player -> action
        yield (rand_player, rand_action)


def consume_event(
    events: list[tuple[str, str]]
) -> typing.Generator[tuple[str, str], None, None]:
    while events:
        # Randomiza um número do tamanho da lista 
        random_index = random.randint(0, len(events) - 1)

        # Pop garante que antes de remover eu ainda tenha o dado para yield
        remove = events.pop(random_index)
        yield remove

if __name__ == "__main__":

    # next para passar ao proximo yield a cada iteracao
    gen = gen_event()

    for i in range(1000):
        # Avança gen 1 yield: retoma o while suspenso e devolve a próxima tupla
        event = next(gen)
        print(f"Event {i}: Player {event[0]} did action {event[1]}")

    # Criando a lista de 10
    lista_10: list[tuple[str, str]] = []
    for _ in range (10):
        lista_10.append(next(gen))

    print(f"\nBuilt list of 10 events: {lista_10}\n")

    for evento in consume_event(lista_10):

        print(f"Got event from list: {evento}")

        print(f"Remains in list: {lista_10}\n")