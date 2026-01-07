import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Zkontrolujte, zda je zadaná e-mailová adresa platná. Například, abc.123@def.ghi.com.uk je platná e-mailová adresa. Pokryjte co nejvíce případů, abyste se vyhnuli falešným negativům.

    Args:
        email: E-mail, který se má zkontrolovat.

    Returns:
        Tuple[bool, str]: N-tice, kde první prvek je boolean indikující, zda je e-mail platný, a druhý prvek je vzor použitý k ověření e-mailu."""
    # Komplexní regulární výraz pro validaci e-mailu podle RFC 5322
    pattern = r'''^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@
    (?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$'''
    
    # Kompilace vzoru s re.VERBOSE pro lepší čitelnost a re.IGNORECASE pro nezávislost na velikosti písmen
    compiled_pattern = re.compile(pattern, re.VERBOSE | re.IGNORECASE)
    
    # Ověření e-mailu
    is_valid = bool(compiled_pattern.match(email))
    
    return (is_valid, pattern)