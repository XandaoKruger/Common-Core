from abc import ABC, abstractmethod

class Creature(ABC):
    def __init__(self, nome: str, creature_type: str) -> None:
        self.nome = nome
        self.creature_type = creature_type

    @abstractmethod
    def attack(self) -> str:
        ...

    def describe(self) -> str:
        return f"{self.nome} is a {self.creature_type} type Creature"


class Charmander(Creature):
    def __init__(self) -> None:
        super().__init__("Charmander", "Fire")

    def attack(self) -> str:
        return f"{self.nome} uses Ember!"


class Charmeleon(Creature):
    def __init__(self) -> None:
        super().__init__("Charmeleon", "Fire/Flying")

    def attack(self) -> str:
        return f"{self.nome} uses Flamethrower!"


class Squirtle(Creature):
    def __init__(self) -> None:
        super().__init__("Squirtle", "Water")

    def attack(self) -> str:
        return f"{self.nome} uses Water Gun!"


class Wartortle(Creature):
    def __init__(self) -> None:
        super().__init__("Wartortle", "Water")

    def attack(self) -> str:
        return f"{self.nome} uses Hydro Pump!"
