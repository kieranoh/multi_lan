import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Controleer of het opgegeven e-mailadres geldig is. Bijvoorbeeld, abc.123@def.ghi.com.uk is een geldig e-mailadres. Dek zoveel mogelijk gevallen af om valse negatieven te voorkomen.

    Args:
        email: Het te controleren e-mailadres.

    Returns:
        Tuple[bool, str]: Een tuple waarbij het eerste element een boolean is die aangeeft of het e-mailadres geldig is en het tweede element het patroon is dat is gebruikt om het e-mailadres te controleren."""
    
    # Regex patroon voor een geldig e-mailadres
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Controleer of het e-mailadres overeenkomt met het patroon
    is_valid = bool(re.match(pattern, email))
    
    return is_valid, pattern