import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Vérifiez si l'adresse e-mail fournie est valide. Par exemple, abc.123@def.ghi.com.uk est une adresse e-mail valide. Couvrez autant de cas que possible pour éviter les faux négatifs.

    Args:
        email: L'e-mail à vérifier.

    Returns:
        Tuple[bool, str]: Un tuple avec le premier élément étant un booléen indiquant si l'e-mail est valide et le deuxième élément étant le motif utilisé pour vérifier l'e-mail."""
    
    # Motif de validation d'une adresse e-mail
    email_pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Vérification de l'adresse e-mail
    is_valid = re.match(email_pattern, email) is not None
    
    return is_valid, email_pattern