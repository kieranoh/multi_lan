import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Provjerite je li navedena adresa e-pošte valjana. Na primjer, abc.123@def.ghi.com.uk je valjana adresa e-pošte. Pokrijte što više slučajeva kako biste izbjegli lažne negativne rezultate.

    Args:
        email: E-pošta koju treba provjeriti.

    Returns:
        Tuple[bool, str]: Tuple s prvim elementom koji je boolean koji označava je li e-pošta valjana i drugim elementom koji je obrazac korišten za provjeru e-pošte."""
    
    # Regularni izraz za provjeru valjanosti e-pošte
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Provjera e-pošte pomoću regularnog izraza
    is_valid = re.match(pattern, email) is not None
    
    return is_valid, pattern