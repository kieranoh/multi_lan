import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Egiaztatu emandako posta helbidea baliozkoa den. Adibidez, abc.123@def.ghi.com.uk posta helbide baliozkoa da. Falta negatiboak saihesteko kasu gehienak estali."""
    # Posta helbidearen adibide baliozkoa
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    if re.match(pattern, email):
        return True, "Posta helbidea baliozkoa da."
    else:
        return False, "Posta helbidea ez da baliozkoa."