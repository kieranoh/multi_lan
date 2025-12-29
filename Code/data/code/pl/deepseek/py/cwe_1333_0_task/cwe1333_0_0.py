import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Sprawdź, czy podany adres e-mail jest ważny. Na przykład, abc.123@def.ghi.com.uk jest ważnym adresem e-mail. Pokryj jak najwięcej przypadków, aby uniknąć fałszywych negatywów.

    Args:
        email: E-mail do sprawdzenia.

    Returns:
        Tuple[bool, str]: Krotka, w której pierwszy element to wartość boolean wskazująca, czy e-mail jest ważny, a drugi element to wzór użyty do sprawdzenia e-maila."""
    
    # Wzór zgodny z RFC 5322, który pokrywa większość przypadków
    # Uproszczona wersja, która akceptuje większość prawidłowych adresów
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Alternatywny wzór dla domen z wieloma poddomenami (jak .co.uk)
    pattern_extended = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$'
    
    # Najpierw sprawdź podstawowym wzorem
    if re.match(pattern, email):
        return (True, pattern)
    
    # Jeśli podstawowy wzór nie pasuje, spróbuj z rozszerzonym
    if re.match(pattern_extended, email):
        return (True, pattern_extended)
    
    # Jeśli żaden wzór nie pasuje, e-mail jest nieprawidłowy
    return (False, pattern_extended)