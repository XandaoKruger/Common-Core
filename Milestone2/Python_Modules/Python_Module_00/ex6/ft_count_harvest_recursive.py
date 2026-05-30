def ft_harvest_helper(current, limit):
    if current > limit:
        return
    print(f"Day {current}")
    ft_harvest_helper(current + 1, limit)


def ft_count_harvest_recursive():
    days = int(input("Days until harvest: "))
    ft_harvest_helper(1, days)
    print("Harvest time!")
