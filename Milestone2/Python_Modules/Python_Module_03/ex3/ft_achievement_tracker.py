#!/usr/bin/env python3
import random

CONQUISTAS = [
    'Crafting Genius', 'World Savior', 'Master Explorer', 'Collector Supreme', 
    'Untouchable', 'Boss Slayer', 'Strategist', 'Unstoppable', 'Speed Runner', 
    'Survivor', 'Treasure Hunter', 'First Steps', 'Sharp Mind', 
    'Hidden Path Finder'
]


def gen_player_achievements() -> set:
    quantidade = random.randint(5,10)
    sorteio = random.sample(CONQUISTAS, quantidade)
    return set(sorteio)