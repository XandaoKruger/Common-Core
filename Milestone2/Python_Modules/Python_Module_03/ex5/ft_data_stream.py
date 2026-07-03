#!/usr/bin/env python3

import typing
import random

PLAYERS = ["Bob", "Alice", "Dylan", "Charlie"]

ACTIONS = [
    "run", "eat", "sleep", "grab", "climb", "move", "swim", "use", "release"
]


def gen_event() -> typing.Generator[tuple[str, str], None, None]:
    