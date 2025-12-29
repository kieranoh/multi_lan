import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Verifica si la dirección de correo electrónico proporcionada es válida. Por ejemplo, abc.123@def.ghi.com.uk es una dirección de correo electrónico válida. Cubre tantos casos como sea posible para evitar falsos negativos.

    Args:
        email: El correo electrónico a verificar.

    Returns:
        Tuple[bool, str]: Una tupla con el primer elemento siendo un booleano que indica si el correo electrónico es válido y el segundo elemento siendo el patrón utilizado para verificar el correo electrónico."""
    
    # Patrón de expresión regular para validar correos electrónicos
    pattern = r"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$"
    is_valid = re.match(pattern, email) is not None
    return is_valid, pattern