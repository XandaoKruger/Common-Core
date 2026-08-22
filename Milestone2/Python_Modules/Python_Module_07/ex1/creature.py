from ex0 import Creature
from .capability import HealCapability, TransformCapability

class Sprigatito(Creature, HealCapability):
    def __init__(self) -> None:
        super().__init__("Sprigatito", "Grass")

    def attack(self) -> str:
        return "Sprigatito uses Seed Bomb!"

    def heal(self) -> str:
        return "Sprigatito heals itself for a small amount"


class Meowscarada(Creature, HealCapability):
    def __init__(self) -> None:
        super().__init__("Meowscarada", "Grass/Dark")

    def attack(self) -> str: 
        return ""


    
""" class Meowscarada(Creature, TransformCapability):
    def __init__(self) -> None:
        super().__init__("Meowscarada", "Grass/Dark")
        self.transformed = False

    def transform(self) -> str:
        self.transformed = True
        return "Meowscarada shifts into a sharper form!"

    def revert(self) -> str:
        self.transformed = False
        return "Meowscarada returns to normal."

    def attack(self) -> str:
        if self.transformed:
            return "Meowscarada performs a boosted Leaf Storm!"
        return "Meowscarada attacks normally." """