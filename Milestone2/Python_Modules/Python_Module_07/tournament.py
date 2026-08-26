#!/usr/bin/env python3

from ex0 import FlameFactory, AquaFactory, CreatureFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import (
    BattleStrategy, NormalStrategy, AgressiveStrategy,
    DefensiveStrategy, InvalidStrategy
)

def battle(opponents: list[tuple[CreatureFactory, BattleStrategy]]) -> None:
    print("*** Tournament ***")
    print(f"{len(opponents)} opponents involved\n")

    for i in range(len(opponents)):
        for j in range(i + 1, len(opponents)):
            factory1, strategy1 = opponents[i]
            factory2, strategy2 = opponents[j]

            creature1 = factory1.create_base()
            creature2 = factory2.create_base()

            print("* Battle *")
            print(creature1.describe())
            print(" vs.")
            print(creature2.describe())
            print(" now fight!")

            try:
                print(strategy1.act(creature1))
                print(strategy2.act(creature2))
            except InvalidStrategy as e:
                print(f"Battle error, aborting tournament: {e}")
                return

            print()


if __name__ == "__main__":

    # FACTORYS
    flame_factory = FlameFactory()
    aqua_factory = AquaFactory()
    healing_factory = HealingCreatureFactory()
    transform_factory = TransformCreatureFactory()

    # STRATEGYS
    normal_strategy = NormalStrategy()
    agressive_strategy = AgressiveStrategy()
    defense_strategy = DefensiveStrategy()
     
    tournaments = [
        (
        "Tournament 0 (basic)",
        " [ (Flame+Normal), (Healing+Defensive) ]",
        [
        (flame_factory, normal_strategy),
        (healing_factory, defense_strategy)
        ]),
        (
        "Tournament 1 (error)",
        " [ (Flame+Aggressive), (Healing+Defensive) ]",
        [
        (flame_factory, agressive_strategy),
        (healing_factory, defense_strategy)
        ]),
        (
        "Tournament 2 (multiple)",
        " [ (Aqua+Normal), (Healing+Defensive), (Transform+Aggressive) ]",
        [
        (aqua_factory, normal_strategy),
        (healing_factory, defense_strategy),
        (transform_factory, agressive_strategy)
        ]),
    ]

    for name, description, opponents in tournaments:
        print(f"\n{name}")
        print(f"\n{description}")
        battle(opponents)
