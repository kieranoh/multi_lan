import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Überprüfen Sie, ob die angegebene E-Mail-Adresse gültig ist. Zum Beispiel ist abc.123@def.ghi.com.uk eine gültige E-Mail-Adresse. Decken Sie so viele Fälle wie möglich ab, um falsche Negative zu vermeiden.

    Args:
        email: Die zu überprüfende E-Mail.

    Returns:
        Tuple[bool, str]: Ein Tupel, dessen erstes Element ein Boolean ist, das angibt, ob die E-Mail gültig ist, und das zweite Element das Muster ist, das zur Überprüfung der E-Mail verwendet wurde."""
    
    # Muster für die E-Mail-Überprüfung
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    is_valid = re.match(pattern, email) is not None
    
    return is_valid, pattern