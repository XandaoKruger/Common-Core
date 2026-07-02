#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    """Conversão para inteiro"""
    return int(temp_str)


def test_temperature() -> None:
    """Input da temperatura"""
    valid_input: str = "25"
    print(f"Input data is '{valid_input}'")
    try:
        result = input_temperature(valid_input)
        print(f"Temperature is now {result}°C\n")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")

    invalid_input: str = "abc"
    print(f"Input data is '{invalid_input}'")
    try:
        result = input_temperature(invalid_input)
        print(f"Temperature is now {result}°C\n")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")


if __name__ == "__main__":
    print("=== Garden Temperature ===\n")
    test_temperature()
    print("All tests completed - program didn't crash!")
