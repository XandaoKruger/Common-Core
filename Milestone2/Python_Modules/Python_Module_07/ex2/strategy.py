from abc import ABC, abstractmethod
from ex0 import Creature
from ex1 import TransformCreature, HealCreature


class InvalidStrategy(Exception):
    ...


class BattleStrategy(ABC):
    @abstractmethod
    def is_valid(self, creature: Creature) -> bool:
        ...

    @abstractmethod
    def act(self, creature: Creature) -> str:
        ...


class NormalStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return True

    def act(self, creature: Creature) -> str:
        return creature.attack()


class AgressiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, TransformCreature)

    def act(self, creature: Creature) -> str:
        if not isinstance(creature, TransformCreature):
            raise InvalidStrategy(
                f"Invalid Creature '{creature.nome}' for this agressive \
strategy"
            )

        transform_msg = creature.transform()
        attak_msg = creature.attack()
        revert_msg = creature.revert()

        return f"{transform_msg}\n{attak_msg}\n{revert_msg}"


class DefensiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, HealCreature)

    def act(self, creature: Creature) -> str:
        if not isinstance(creature, HealCreature):
            raise InvalidStrategy(
                f"Invalid Creature '{creature.nome}' for this defensive \
strategy"
            )

        heal_msg = creature.heal()
        atk_msg = creature.attack()

        return f"{atk_msg}\n{heal_msg}"
