from .creature import Meowscarada, Sprigatito, Dragapult, Dreepy
from .creature import HealCreature, TransformCreature
from ex0 import CreatureFactory


class HealingCreatureFactory(CreatureFactory):
    # Aqui retorno a classe genérica para poder importar para capacitor depois.
    def create_base(self) -> HealCreature:
        return Sprigatito()

    def create_evolved(self) -> HealCreature:
        return Meowscarada()


class TransformCreatureFactory(CreatureFactory):
    def create_base(self) -> TransformCreature:
        return Dreepy()

    def create_evolved(self) -> TransformCreature:
        return Dragapult()
