#!/usr/bin/env python3
import random

# CONQUISTAS - uppercase para indicar que é constante e global.
# Lista fixa, não muda durante a execução
CONQUISTAS = [
    'Crafting Genius', 'World Savior', 'Master Explorer', 'Collector Supreme',
    'Untouchable', 'Boss Slayer', 'Strategist', 'Unstoppable', 'Speed Runner',
    'Survivor', 'Treasure Hunter', 'First Steps', 'Sharp Mind',
    'Hidden Path Finder', 'Night Owl', 'Iron Will', 'Lucky Strike',
    'Puzzle Master', 'Marathon Runner', 'Shadow Walker', 'Loot Goblin',
    'Final Boss', 'Pathfinder', 'Glass Cannon'
]


def gen_player_achievements() -> set[str]:
    # Randint para randomizar entre 13 e 17
    quantidade = random.randint(13, 17)

    # Escolhe SEM repetir, dentro da quantidade (que é aleatorizada a cima)
    sorteio = random.sample(CONQUISTAS, quantidade)
    return set(sorteio)


if __name__ == "__main__":
    print("=== Achievement Track System ===\n")

    # Variaveis de controle
    alice = gen_player_achievements()
    bob = gen_player_achievements()
    charlie = gen_player_achievements()
    dylan = gen_player_achievements()

    # Lista que guarda tuplas, para utilizar no for abaixo.
    # ("Coloca o nome" para cada variavel)
    exibicao = [
        ("Alice", alice), ("Bob", bob), ("Charlie", charlie), ("Dylan", dylan)
    ]

    # For que para cada nome, usa a variavel na lista de exibicao
    for nome, conjunto in exibicao:
        print(f"Player {nome}: {conjunto}")

    # Val para ver todas as conquistas que foram recebidas entre os jogadores
    total_conqu = alice.union(bob, charlie, dylan)
    print(f"\nAll distinct achievements: {total_conqu}")

    # Var para ver a conquista que todos tem igual.
    igual = alice.intersection(bob, charlie, dylan)
    print(f"\nCommon achievements: {igual}\n")

    for nome, conjunto in exibicao:
        # Cria um saco vazio para guardar todos os achievments dos outros
        outros: set[str] = set()
        # Mais um loop para comparar um jogador com outro jogador
        for n, c in exibicao:
            # Verificar se não é o mesmo jogador
            if n != nome:
                # Utiliza o saco vazio para receber e guardar as conquistas
                # do jogador, se for repetida, não coloca por causa do set.
                # Faz isso para todos os jogadores, e no final compara com
                # o jogador primário.
                outros = outros.union(c)

        # Exclusivo recebe apenas a conquista que só o {nome} tem, difference
        # se encarrega de observar se não há iguais, sobrando só as conquistas
        # que aleque jogador tem em exclusivo.
        # Resumo: Retirando o que os "outros" tem, do conjunto
        exclusivo = conjunto.difference(outros)
        print(f"Only {nome} has: {exclusivo}")

    # Transformando as conquistas em set (conjunto) para poder executar as
    # funções matematicas de set (union, difference, intersection...)
    all_achiev = set(CONQUISTAS)
    print()
    for nome, conjunto in exibicao:
        faltando = all_achiev.difference(conjunto)
        print(f"{nome} is missing: {faltando}")
