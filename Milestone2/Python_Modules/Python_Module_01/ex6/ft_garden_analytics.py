#!/usr/bin/env python3

class Plant():
    """Classe mae atualizada com sistema de Analiytics"""
    class PlantStats():
        """Guarda os dados estaticos internos de cada planta"""
        def __init__(self) -> None:
            pass
        def display(self) -> None:
            pass
    
    
    
    
    def __init__(
        self, name: str, _height: float, _age: int, growth_rate: float
    ) -> None:
        self.name = name
        self._height = _height if _height >= 0 else 0.0
        self._age = _age if _age >= 0 else 0
        self.growth_rate = growth_rate
