#!/usr/bin/env python3

class Plant:
    """Classe capaz de resgistrar o crescimento de uma planta"""
    name: str
    age: int
    height: float
    growth_rate: float

    def grow(self) -> None:
        """Aumenta a altura da planta com base no crescimento"""
        self.height += self.growth_rate
        self.height = round(self.height, 1)

    def age_plant(self) -> None:
        """Aumenta a idade da planta em 1 dia"""
        self.age += 1

    def show(self) -> None:
        """Exibe as informações da planta"""
        print(f"{self.name}: {self.height}cm, {self.age} days old")


if __name__ == "__main__":
    print("=== Garden Plant Growth ===")
    rose = Plant()
    rose.name = "Rose"
    rose.age = 30
    rose.growth_rate = 0.8
    inicial_rate = rose.height = 25.0
    rose.show()

    for c in range(1, 8):
        rose.grow()
        rose.age_plant()
        print(f"=== Day {c} ===")
        rose.show()

    total_growth = rose.height - inicial_rate
    total_growth = round(total_growth, 1)
    print(f"Growth this week: {total_growth}cm")
