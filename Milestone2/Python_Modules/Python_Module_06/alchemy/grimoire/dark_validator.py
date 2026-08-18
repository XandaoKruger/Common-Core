from .dark_spellbook import dark_spell_allowed_ingredients


def validate_dark_ingredients(ingredients: str) -> str:

    allowed = dark_spell_allowed_ingredients()

    ingredients_lower = ingredients.lower()

    is_valid = False
    for item in allowed:
        if item in ingredients_lower:
            is_valid = True

    if is_valid:
        status = "VALID"
    else:
        status = "INVALID"

    return f"{ingredients} - {status}"
