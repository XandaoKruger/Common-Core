#!/usr/bin/env python3

from ex0 import FlameFactory, AquaFactory, CreatureFactory


def test_factory(factory: CreatureFactory) -> None:
    print("\nTesting factory\n")

    base = factory.create_base()
    evolved = factory.create_evolved()

    print(base.describe())
    print(base.attack())

    print(evolved.describe())
    print(evolved.attack())


def test_battle(flame: CreatureFactory, aqua: CreatureFactory) -> None:
    print("\nTesting battle\n")

    base_fire = flame.create_base()
    base_aqua = aqua.create_base()

    print(base_fire.describe())
    print("vs.")
    print(base_aqua.describe())
    print("fight!")
    print(base_fire.attack())
    print(base_aqua.attack())


if __name__ == "__main__":
    flame_factory = FlameFactory()
    aqua_factory = AquaFactory()

    test_factory(flame_factory)
    test_factory(aqua_factory)
    test_battle(flame_factory, aqua_factory)
