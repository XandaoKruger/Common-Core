#!/usr/bin/env python3

class Plant():
    """Classe mae atualizada com sistema de Analiytics"""
    class PlantStats():
        """Guarda os dados estaticos internos de cada planta"""
        def __init__(self) -> None:
            self.grow_count: int = 0
            self.age_count: int = 0
            self.show_count: int = 0
            self.shade_count: int = 0

        def display(self, is_tree: bool = False) -> None:
            """Exibe as estatisticas"""
            print(f"{self.grow_count} grow, {self.age_count} age, ", end="")
            print(f"{self.show_count} show")
            if is_tree:
                print(f"{self.shade_count} shade")
    
    def __init__(
        self, name: str, height: float, age: int, growth_rate: float
    ) -> None:
        self.name = name
        self._height = height if height >= 0 else 0.0
        self._age = age if age >= 0 else 0
        self.growth_rate = growth_rate
        self._stats = self.PlantStats()

    def show(self) -> None:
        """Mostra as iformações das plantas"""
        self._stats.show_count += 1
        print(f"{self.name}: {self._height}cm, {self.age} days old")

    def age_plant(self) -> None:
        """Aumenta age em um (1) dia"""
        self._stats.grow_count += 1
        self._height += self.growth_rate
        self._height = round(self._height, 1)

class Flower(Plant):
    def __init__(self, name, height, age, growth_rate):
        super().__init__(name, height, age, growth_rate)
