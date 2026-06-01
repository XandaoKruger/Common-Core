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
    def __init__(self, name, height, age, growth_rate, color: str) -> None:
        super().__init__(name, height, age, growth_rate)
        self.color = color
        self.has_bloomed: bool = False

    def show(self) -> None:
        """Sobrepoe o show da classe mae para exbir os dois"""
        super().show()
        print(f"Color: {self.color}")
        if not self.has_bloomed:
            print(f"{self.name} has not bloomed yet")
        else:
            print(f"{self.name} is blooming beautifully!")

    def bloom(self) -> None:
        """Altera o estado da flor para floreida"""
        self.has_bloomed = True


class Tree(Plant):
    """Classe espeializada em arvores"""
    def __init__(
        self, name, height, age, growth_rate, trunk_diameter: float
    ) -> None:
        super().__init__(name, height, age, growth_rate)
        self.trunk_diameter = trunk_diameter

    def show(self) -> None:
        """Sobrepoe o show da clase mae para exibir o da arvore """
        super().show()
        print(f"Trunk diameter: {self.trunk_diameter}cm")

    def produce_shade(self) -> None:
        """Imprime a mensagem de sombra projetada"""
        print(f"Tree {self.name} now produces a shade of ", end="")
        print(f"{self.get_height()}cm long and {self.trunk_diameter}cm wide")


class Vegetable(Plant):
    """Classe especializada em vegetais"""
    def __init__(
        self, name, height, age, growth_rate, harvest_season: str
    ) -> None:
        super().__init__(name, height, age, growth_rate)
        self.harvest_season = harvest_season
        self.nutritional_value: int = 0

    def show(self) -> None:
        """Sobrepoe o show mae para este"""
        super().show()
        print(f"Harvest season: {self.harvest_season}")
        print(f"nutritional value: {self.nutritional_value}")

    def age_plant(self) -> None:
        """Chama a mae e aumenta o valor nutricional"""
        super().age_plant()
        self.nutritional_value += 1

    def grow(self) -> None:
        """Chama o crescimento padrão da mãe"""
        super().grow()


if __name__ == "__main__":
    print("=== Garden Plant Types ===")
    print("=== Flower")

    rose = Flower("Rose", 15.0, 10, 0.0, "red")
    rose.show()
    print("[asking the rose to bloom]")
    rose.bloom()
    rose.show()

    print("=== Tree")

    oak = Tree("Oak", 200.0, 365, 0.0, 5.0)
    oak.show()
    print("[asking the oak to produce shade]")
    oak.produce_shade()

    print("=== Vegetable")

    tomato = Vegetable("Tomato", 5.0, 10, 2.1, "April")
    tomato.show()
    print("[make tomato grow and age for 20 days]")
    for tomate in range(20):
        tomato.age_plant()
        tomato.grow()
    tomato.show()
