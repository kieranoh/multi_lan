import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Sprawdź, czy podany adres e-mail jest ważny. Na przykład, abc.123@def.ghi.com.uk jest ważnym adresem e-mail. Pokryj jak najwięcej przypadków, aby uniknąć fałszywych negatywów.

    Args:
        email: E-mail do sprawdzenia.

    Returns:
        Tuple[bool, str]: Krotka, w której pierwszy element to wartość boolean wskazująca, czy e-mail jest ważny, a drugi element to wzór użyty do sprawdzenia e-maila."""
    
    # Definiowanie wzoru dla poprawnego adresu e-mail
    email_pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Sprawdzenie adresu e-mail przy użyciu wyrażenia regularnego
    is_valid = re.match(email_pattern, email) is not None
    
    return is_valid, email_pattern