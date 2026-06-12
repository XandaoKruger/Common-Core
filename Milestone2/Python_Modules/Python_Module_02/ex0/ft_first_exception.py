#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    """Conversão para inteiro"""
    return int(temp_str)


def test_temperature() -> None:
    """Input da temperatura"""
    print("Input data is '25'")
    try:
        result = input_temperature("25")
        print(f"Temperature is now {result}°C\n")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")

    print("Input data is 'abc'")
    try:
        result = input_temperature("abc")
        print(f"Temperature is now {result}°C\n")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")


if __name__ == "__main__":
    print("=== Garden Temperature ===\n")
    test_temperature()
    print("All tests completed - program didn't crash!")
