from ex0 import Creature
from .capability import HealCapability, TransformCapability


# Precisei cirar isso pra abranger mais as criaturas, caso contrário depois eu
# ficaria preso em retornar as criaturas em específico, tirando a
# versatibilidade do código. Assim eu crio apenas uma classe que abrange as
# criaturas que tem esse tipo de "poder" e posso retornar a classe, fazendo o
# mypy aceitar heal() por exemplo, no capacitor.py
class HealCreature(Creature, HealCapability):
    pass


class TransformCreature(Creature, TransformCapability):
    pass


class Sprigatito(HealCreature):
    def __init__(self) -> None:
        super().__init__("Sprigatito", "Grass")

    def attack(self) -> str:
        return "Sprigatito uses Seed Bomb!"

    def heal(self) -> str:
        return "Sprigatito heals itself for a small amount"


class Meowscarada(HealCreature):
    def __init__(self) -> None:
        super().__init__("Meowscarada", "Grass/Dark")

    def attack(self) -> str:
        return "Meowscarada uses Leaf Storm!"

    def heal(self) -> str:
        return "Meowscarada heals itself and others for a large amount"


class Dreepy(TransformCreature):
    def __init__(self) -> None:
        super().__init__("Dreepy", "Dragon/Ghost")
        self.transformed = False

    def transform(self) -> str:
        self.transformed = True
        return "Dreepy shifts into a sharper form!"

    def revert(self) -> str:
        self.transformed = False
        return "Dreepy returns to normal."

    def attack(self) -> str:
        if self.transformed:
            return "Dreepy performs a boosted Dragon Breath!"
        return "Dreepy attacks normally."


class Dragapult(TransformCreature):
    def __init__(self) -> None:
        super().__init__("Dragapult", "Dragon/Ghost")
        self.transformed = False

    def transform(self) -> str:
        self.transformed = True
        return "Dragapult shifts into a sharper form!"

    def revert(self) -> str:
        self.transformed = False
        return "Dragapult returns to normal."

    def attack(self) -> str:
        if self.transformed:
            return "Dragapult performs a powerful Dragon Rush!"
        return "Dragapult attacks normally."
