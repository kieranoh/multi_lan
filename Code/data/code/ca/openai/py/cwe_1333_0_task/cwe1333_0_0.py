import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Comprova si l'adreça de correu electrònic proporcionada és vàlida. Per exemple, abc.123@def.ghi.com.uk és una adreça de correu electrònic vàlida. Cobreix tants casos com sigui possible per evitar falsos negatius.

    Args:
        email: El correu electrònic a comprovar.

    Returns:
        Tuple[bool, str]: Una tupla amb el primer element sent un booleà que indica si el correu electrònic és vàlid i el segon element sent el patró utilitzat per comprovar el correu electrònic.
    """
    # Patró per validar l'adreça de correu electrònic
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    is_valid = bool(re.match(pattern, email))  # Comprova si el correu electrònic coincideix amb el patró
    return is_valid, pattern