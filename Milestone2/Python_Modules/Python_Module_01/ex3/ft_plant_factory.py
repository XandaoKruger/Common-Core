#!/usr/bin/env python3

class Plant():
    """Classe que inicializa e exibe as informaçoes da planta"""
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age

    def show(self) -> None:
        """Mostra as informações da planta"""
        print(f"{self.name}: {self.height}cm, {self.age} days old")


if __name__ == "__main__":
    print("=== Plant Factory Output ===")
    garden = [
        Plant("Rose", 25.0, 30),
        Plant("Oak", 200.0, 365),
        Plant("Cactus", 5.0, 90),
        Plant("Sunflower", 80.0, 45),
        Plant("Fern", 15.0, 120)
    ]

    for plant in garden:
        print("Created: ", end="")
        plant.show()
