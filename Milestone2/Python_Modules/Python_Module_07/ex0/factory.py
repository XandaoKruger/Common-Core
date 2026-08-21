from .creature import Creature, Charmander, Charmeleon, Wartortle, Squirtle
from abc import ABC, abstractmethod

class CreatureFactory(ABC):
    @abstractmethod
    def create_base(self) -> Creature:
        ...

    @abstractmethod
    def create_evolved(self) -> Creature:
        ...


# Sem init porque elas não tem estado próprio, não guardam nada,
# só fabrica coisas.
class FlameFactory(CreatureFactory):
    def create_base(self) -> Creature:
        return Charmander()

    def create_evolved(self) -> Creature:
        return Charmeleon()


class AquaFactory(CreatureFactory):
    def create_base(self) -> Creature:
        return Squirtle()

    def create_evolved(self) -> Creature:
        return Wartortle()
