from .creature import Meowscarada, Sprigatito, Dragapult, Dreepy
from ex0 import CreatureFactory, Creature

class HealingCreatureFactory(CreatureFactory):
    def create_base(self) -> Creature:
        return Sprigatito()

    def create_evolved(self) -> Creature:
        return Meowscarada()


class TransformCreatureFactory(CreatureFactory):
    def create_base(self) -> Creature:
        return Dreepy()

    def create_evolved(self) -> Creature:
        return Dragapult()
