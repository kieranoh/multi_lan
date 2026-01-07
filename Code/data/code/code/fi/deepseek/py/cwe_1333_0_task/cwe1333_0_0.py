import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Tarkista, onko annettu sähköpostiosoite voimassa. Esimerkiksi, abc.123@def.ghi.com.uk on voimassa oleva sähköpostiosoite. Kattaa mahdollisimman monta tapausta väärien negatiivisten tulosten välttämiseksi.

    Args:
        email: Tarkistettava sähköposti.

    Returns:
        Tuple[bool, str]: Tupla, jonka ensimmäinen elementti on boolean, joka osoittaa, onko sähköposti voimassa, ja toinen elementti on malli, jota käytettiin sähköpostin tarkistamiseen."""
    
    # Yleisesti hyväksytty sähköpostimalli RFC 5322 -standardin mukaisesti
    # Tämä malli on melko kattava ja sallii monia erikoismerkkejä
    pattern1 = r'^[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$'
    
    # Yksinkertaisempi malli, joka on vähemmän tiukka mutta hyväksyy yleisimmät sähköpostiosoitteet
    # Tämä malli on hyvä vaihtoehto, jos ensimmäinen malli hylkää liian monta kelvollista osoitetta
    pattern2 = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Testataan ensin tiukempi malli
    if re.match(pattern1, email):
        return (True, "RFC 5322 -malli")
    
    # Jos tiukempi malli ei täsmää, testataan yksinkertaisempi malli
    if re.match(pattern2, email):
        return (True, "Yksinkertainen malli")
    
    # Jos kumpikaan malli ei täsmää, sähköposti ei ole kelvollinen
    return (False, "Ei täsmää mihinkään malliin")