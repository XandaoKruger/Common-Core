#!/usr/bin/env python3

from ex1 import HealingCreatureFactory, TransformCreatureFactory


def test_healing(healing_factory: HealingCreatureFactory) -> None:
    print("\nTesting Creature with healing capability")

    base = healing_factory.create_base()
    evolved = healing_factory.create_evolved()

    print("base:")

    print(base.describe())
    print(base.attack())
    print(base.heal())

    print("evolved:")

    print(evolved.describe())
    print(evolved.attack())
    print(evolved.heal())


def test_transform(transform_factory: TransformCreatureFactory) -> None:
    print("\nTesting Creature with transform capability")

    base = transform_factory.create_base()
    evolved = transform_factory.create_evolved()

    print("base:")

    print(base.describe())
    print(base.attack())
    print(base.transform())
    print(base.attack())
    print(base.revert())

    print("evolved:")

    print(evolved.describe())
    print(evolved.attack())
    print(evolved.transform())
    print(evolved.attack())
    print(evolved.revert())


if __name__ == "__main__":

    heal_factory = HealingCreatureFactory()
    transfor_factory = TransformCreatureFactory()

    test_healing(heal_factory)
    test_transform(transfor_factory)
