import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Controleer of het opgegeven e-mailadres geldig is. Bijvoorbeeld, abc.123@def.ghi.com.uk is een geldig e-mailadres. Dek zoveel mogelijk gevallen af om valse negatieven te voorkomen.

    Args:
        email: Het te controleren e-mailadres.

    Returns:
        Tuple[bool, str]: Een tuple waarbij het eerste element een boolean is die aangeeft of het e-mailadres geldig is en het tweede element het patroon is dat is gebruikt om het e-mailadres te controleren."""
    
    # Patroon 1: Basis RFC 5322-compatibel patroon dat veel voorkomende e-mailformaten dekt
    pattern1 = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Patroon 2: Uitgebreider patroon dat subdomeinen en langere TLD's ondersteunt (zoals .com.uk)
    pattern2 = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$'
    
    # Patroon 3: Patroon dat quotes en speciale karakters in lokale deel ondersteunt
    pattern3 = r'^("([^"]|\\.)+"|[a-zA-Z0-9._%+-]+)@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$'
    
    # Patroon 4: Patroon dat IP-adressen in domeindeel ondersteunt (bijv. user@[192.168.1.1])
    pattern4 = r'^("([^"]|\\.)+"|[a-zA-Z0-9._%+-]+)@(\[(\d{1,3}\.){3}\d{1,3}\]|[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*)$'
    
    # Test de e-mail tegen de patronen in volgorde van specificiteit
    patterns = [
        ("RFC 5322 basis patroon", pattern1),
        ("Uitgebreid domein patroon", pattern2),
        ("Quotes in lokale deel", pattern3),
        ("IP-adres in domein", pattern4)
    ]
    
    for pattern_name, pattern in patterns:
        if re.match(pattern, email):
            return (True, pattern_name)
    
    # Als geen enkel patroon matcht, retourneer False met het meest uitgebreide patroon
    return (False, "Geen patroon matcht")