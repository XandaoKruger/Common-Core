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
            print(f"Stats: {self.grow_count} grow, {self.age_count} age, ", end="")
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
        print(f"{self.name}: {self._height}cm, {self._age} days old")

    def age(self) -> None:
        """Aumenta age em um (1) dia"""
        self._stats.age_count += 1
        self._age += 1

    def grow(self) -> None:
        """Aumenta altura da planta com base no crescimento"""
        self._stats.grow_count += 1
        self._height += self.growth_rate
        self._height = round(self._height, 1)

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

    @staticmethod
    def is_older_than_an_year(age: int) -> bool:
        """Confere se a planta e mais velha que um ano"""
        return age > 365
    
    @classmethod
    def anonymous(cls) -> Plant:
        """Cria uma instancia de uma planta anonima, sem dados iniciais"""
        return cls(name="Unknown plant", height=0.0, age=0, growth_rate=0.0)


class Flower(Plant):
    """Classe especializada para flores"""
    def __init__(
        self, name: str, height: float, age: int, growth_rate: float, color: str
    ) -> None:
        super().__init__(name, height, age, growth_rate)
        self.color = color
        self.has_bloomed: bool = False

    def show(self) -> None:
        """Sobrepoe o show da classe mae e atualiza as estatisticas"""
        super().show()
        print(f"Color: {self.color}")
        if not self.has_bloomed:
            print(f"{self.name} has not bloomed yet")
        else:
            print(f"{self.name} is blooming beautifully!")

    def bloom(self) -> None:
        """Altera o estado da flor para florida"""
        self.has_bloomed = True


class Seed(Flower):
    """Classe especializada para sementes, herda de flor"""
    def __init__(
        self, name: str, height: float, age: int, growth_rate: float, color: str
    ) -> None:
        super().__init__(name, height, age, growth_rate, color)
        self.seeds_count: int = 0

    def show(self) -> None:
        """Sobrepoe o show para exibir os dados de flor com sementes"""
        super().show()
        print(f"Seeds: {self.seeds_count}")

    def bloom(self) -> None:
        """Faz semente desabrochar em flor e gera 42 sementes"""
        super().bloom()
        self.seeds_count = 42


class Tree(Plant):
    """Classe especializada dem arvores"""
    class Stats(Plant.PlantStats):
        # VER ISSO AQUI 
    def __init__(
        self, name: str, height: float, age: int,
        growth_rate: float, trunk_diameter: float
    ) -> None:
        super().__init__(name, height, age, growth_rate)
        self.trunk_diameter = trunk_diameter

    def show(self) -> None:
        """Sobrepoe show para mostrar arvore"""
        super().show()
        print(f"Trunk diameter: {self.trunk_diameter}cm")

    def produce_shade(self) -> None:
        """Imprime a sombra projetada"""
        self._stats.shade_count += 1
        print(f"Tree {self.name} now produces a shade of ", end="")
        print(f"{self.get_height()}cm long and {self.trunk_diameter}cm wide.")


class Vegetable(Plant):
    """Classe especializada em vegetais"""
    def __init__(
        self, name: str, height: float, age: int, growth_rate: float,
        harvest_season: str
    ) -> None:
        super().__init__(name, height, age, growth_rate)
        self.harvest_season = harvest_season
        self.nutritional_value: int = 0

    def show(self) -> None:
        """Sobrepoe show para mosstrar vegetal"""
        super().show()
        print(f"Harvest season: {self.harvest_season}")
        print(f"Nutritional value: {self.nutritional_value}")

    def age(self) -> None:
        """Aumenta o valor nutricional"""
        super().age()
        self.nutritional_value += 1

    def grow(self) -> None:
        """Chama o crescimento padrao da mae"""
        super().grow()


def display_plat_stats(plant: Tree) -> None:
    """Funcao externa para exibir estatisticas de qualquer planta"""
    is_tree = isinstance(plant, Tree)
    plant._stats.display(is_tree)


if __name__: "__main__":
