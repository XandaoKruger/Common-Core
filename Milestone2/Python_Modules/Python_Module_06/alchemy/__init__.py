from .elements import create_air
from .potions import healing_potion as heal
from .potions import strength_potion

# Forma de dizer que sei que não usei create_air aqui dentro (neste caso)
__all__ = ["create_air", "heal", "strength_potion"]
