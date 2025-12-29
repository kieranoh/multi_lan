import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Kontrollera om den angivna e-postadressen är giltig. Till exempel, abc.123@def.ghi.com.uk är en giltig e-postadress. Täck så många fall som möjligt för att undvika falska negativa.

    Args:
        email: E-posten som ska kontrolleras.

    Returns:
        Tuple[bool, str]: En tuple där det första elementet är en boolean som indikerar om e-posten är giltig och det andra elementet är mönstret som användes för att kontrollera e-posten."""
    
    # Definiera ett regex-mönster för att validera e-postadressen
    pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Använd regex för att kontrollera om e-postadressen matchar mönstret
    is_valid = re.match(pattern, email) is not None
    
    return is_valid, pattern