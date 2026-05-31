#!/usr/bin/env python3

class Plant():
    """Classe que inicializa e exibe as plantas"""
    def __init__(
        self, name: str, height: float, age: int, growth_rate: float
    ) -> None:
        """Inicializa as variaveis das informaçoes das plantas"""
        self.name = name
        self.growth_rate = growth_rate
        self._height = height if height >= 0 else 0.0
        self._age = age if age >= 0 else 0

    def show(self) -> None:
        """Mostra as informações da planta"""
        print(f"{self.name}: {self._height}cm, {self._age} days old")

    def get_height(self) -> float:
        """Retorna height de forma segura"""
        return self._height

    def set_height(self, height: float) -> None:
        """Modifica height, garantindo que não é negativa"""
        if height < 0:
            print(f"{self.name}: Error, height can't be negative")
            print("Height update rejected")
        else:
            self._height = round(float(height), 1)
            print(f"Height updated: {int(self._height)}cm")

    def get_age(self) -> int:
        """Retorna age de forma segura"""
        return self._age

    def set_age(self, age: int) -> None:
        """Modifica age, garantindo que não é negativa"""
        if age < 0:
            print(f"{self.name}: Error, age can't be negative")
            print("Age update rejected")
        else:
            self._age = int(age)
            print(f"Age updated: {self._age} days")

    def age_plant(self) -> None:
        """Aumenta age em um dia"""
        self._age += 1

    def grow(self) -> None:
        """Aumenta a altura da planta com base no crescimento"""
        self._height += self.growth_rate
        self._height = round(self._height, 1)


class Flower(Plant):
    """Classe especializada para flores"""
    def __init__(
        self, name, height, age, growth_rate, color: str, # has_bloomed: bool
    ):
        super().__init__(name, height, age, growth_rate)
        self.color = color
        # self.has_bloomed = has_bloomed    RESOLVER ISSO AQUI.
