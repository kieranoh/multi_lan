import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """Tarkista, onko annettu sähköpostiosoite voimassa. Esimerkiksi, abc.123@def.ghi.com.uk on voimassa oleva sähköpostiosoite. Kattaa mahdollisimman monta tapausta väärien negatiivisten tulosten välttämiseksi.

    Args:
        email: Tarkistettava sähköposti.

    Returns:
        Tuple[bool, str]: Tupla, jonka ensimmäinen elementti on boolean, joka osoittaa, onko sähköposti voimassa, ja toinen elementti on malli, jota käytettiin sähköpostin tarkistamiseen."""
    
    # Sähköpostin tarkistamiseen käytettävä säännöllinen lauseke
    email_pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Tarkistetaan, täyttääkö annettu sähköpostiosoite säännöllisen lausekkeen
    is_valid = re.match(email_pattern, email) is not None
    
    return is_valid, email_pattern