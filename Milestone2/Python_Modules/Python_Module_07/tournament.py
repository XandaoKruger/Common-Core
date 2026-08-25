from ex0 import FlameFactory, AquaFactory, CreatureFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import (
    BattleStrategy, NormalStrategy, AgressiveStrategy,
    DefensiveStrategy, InvalidStrategy
)

def battle(opponents: list[tuple[CreatureFactory, BattleStrategy]]) -> None:
    for i in range(len(opponents)):
        for j in range(i + 1, len(opponents)):
            factory1, strategy1 = opponents[i]
            factory2, strategy2 = opponents[j]
    