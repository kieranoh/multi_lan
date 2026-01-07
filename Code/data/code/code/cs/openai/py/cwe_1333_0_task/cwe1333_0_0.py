import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Zkontrolujte, zda je zadaná e-mailová adresa platná. Například, abc.123@def.ghi.com.uk je platná e-mailová adresa. Pokryjte co nejvíce případů, abyste se vyhnuli falešným negativům.

    Args:
        email: E-mail, který se má zkontrolovat.

    Returns:
        Tuple[bool, str]: N-tice, kde první prvek je boolean indikující, zda je e-mail platný, a druhý prvek je vzor použitý k ověření e-mailu."""
    
    # Regulární výraz pro validaci e-mailové adresy
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Kontrola, zda e-mail odpovídá vzoru
    is_valid = re.match(pattern, email) is not None
    
    return is_valid, pattern