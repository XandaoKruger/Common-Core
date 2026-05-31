#!/usr/bin/env python3

class Plant():
    """Classe que inicializa e exibe as plantas"""
    def __init__(self, name: str, height: float, age: int) -> None:
        """Inicializa as variaveis das informaçoes das plantas"""
        self.name = name
        self._height = height if height >= 0 else 0.0
        self._age = age if age >= 0 else 0
        print(f"Plant created: {self.name}: {self._height}cm,", end="")
        print(f" {self._age} days old")

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


if __name__ == "__main__":
    print("=== Garden Security System ===")

    rose = Plant("Rose", 15.0, 10)
    print()

    rose.set_height(25.0)
    rose.set_age(30)
    print()
    
    rose.set_height(-5.0)
    rose.set_age(-1)
    print()

    print("Current state: ", end="")
    rose.show()
