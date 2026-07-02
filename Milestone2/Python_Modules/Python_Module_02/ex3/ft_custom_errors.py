#!/usr/bin/env python3

class GardenError(Exception):
    def __init__(self, message: str = "Unknown garden error") -> None:
        super().__init__(message)

class PlantError(GardenError):
    """Mostrador de erros de plants"""
    def __init__(self, message: str = "Unknown plant error") -> None:
        super().__init__(message)


def test_plant_error() -> None:
    try:
        raise PlantError("The tomato plant is wilting!")
    except PlantError as e:
        print(f"Caught PlantError: {e}")


class WaterError(GardenError):
    """Mostrador de erros de water"""
    def __init__(self, message: str = "Unknown water error") -> None:
        super().__init__(message)


def test_water_error() -> None:
    try:
        raise WaterError("Not enough water in the tank!")
    except WaterError as e:
        print(f"Caught WaterError: {e}")


def all_garden_errors_test() -> None:
    """Testador de todos os erros"""
    try:
        raise PlantError("The tomato plant is wilting!")
    except GardenError as e:
        print(f"Caught GardenError: {e}")

    try:
        raise WaterError("Not enough water in the tank!")
    except GardenError as e:
        print(f"Caught GardenError: {e}")


if __name__ == "__main__":
    print("=== Custom Garden Errors demo ===\n")

    print("Testing PlantError...")
    test_plant_error()

    print("\nTesting WaterError...")
    test_water_error()

    print("\nTesting catching all garden errors...")
    all_garden_errors_test()

    print("\nAll custom error types work correctly")
