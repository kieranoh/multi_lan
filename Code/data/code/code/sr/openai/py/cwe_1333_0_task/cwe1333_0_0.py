import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Proverite da li je navedena adresa e-pošte validna. Na primer, abc.123@def.ghi.com.uk je validna adresa e-pošte. Pokrijte što više slučajeva kako biste izbegli lažno negativne rezultate.

    Args:
        email: E-pošta koju treba proveriti.

    Returns:
        Tuple[bool, str]: Tuple sa prvim elementom koji je boolean koji označava da li je e-pošta validna i drugim elementom koji je obrazac korišćen za proveru e-pošte."""
    
    # Regularni izraz za validaciju email adrese
    pattern = r'^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$'
    
    # Provera da li email odgovara obrascu
    is_valid = re.match(pattern, email) is not None
    
    return is_valid, pattern