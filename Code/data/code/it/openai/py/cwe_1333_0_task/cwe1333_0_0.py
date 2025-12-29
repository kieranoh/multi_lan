import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Controlla se l'indirizzo email fornito è valido. Ad esempio, abc.123@def.ghi.com.uk è un indirizzo email valido. Copri il maggior numero possibile di casi per evitare falsi negativi.

    Args:
        email: L'email da controllare.

    Returns:
        Tuple[bool, str]: Una tupla con il primo elemento che è un booleano che indica se l'email è valida e il secondo elemento che è il modello utilizzato per controllare l'email."""
    
    # Modello regex per controllare la validità dell'email
    email_regex = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Controllo con regex
    is_valid = re.match(email_regex, email) is not None
    
    return is_valid, email_regex