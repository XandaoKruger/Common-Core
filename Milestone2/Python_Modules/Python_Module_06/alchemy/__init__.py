from .elements import create_air
from .potions import healing_potion as heal
from .potions import strength_potion
from .transmutation import lead_to_gold

# Forma de dizer que sei que não usei nada importado aqui dentro (nesse caso)
__all__ = ["create_air", "heal", "strength_potion", "lead_to_gold"]
