def ft_seed_inventory(seed_type: str, quantity: int, unit: str) -> None:
    upper = seed_type.capitalize()
    if unit == 'packets':
        print(f"{upper} seeds: {quantity} {unit} available")
    elif unit == 'grams':
        print(f"{upper} seeds: {quantity} {unit} total")
    elif unit == 'area':
        print(f"{upper} seeds: covers {quantity} square meters")
    else:
        print("Unknown unit type")
