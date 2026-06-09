#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    temp = int(temp_str)
    if temp > 40:
        raise ValueError(f"{temp}°C is too hot for plants (max 40°C)")
    if temp < 0:
        raise ValueError(f"{temp}°C is too cold for plants (min 0°C)")
    return temp


def test_temperature():
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

    print("Input data is '100'")
    try:
        result = input_temperature("100")
        print(f"Temperature is now {result}°C\n")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")

    print("Input data is '-50'")
    try:
        result = input_temperature("-50")
        print(f"Temperature is now {result}°C\n")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")


if __name__ == "__main__":
    print("=== Garden Temperature Checker ===\n")
    test_temperature()
    print("All tests completed - program didn't crash!")
