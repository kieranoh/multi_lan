import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Kontrollera om den angivna e-postadressen är giltig. Till exempel, abc.123@def.ghi.com.uk är en giltig e-postadress. Täck så många fall som möjligt för att undvika falska negativa.

    Args:
        email: E-posten som ska kontrolleras.

    Returns:
        Tuple[bool, str]: En tuple där det första elementet är en boolean som indikerar om e-posten är giltig och det andra elementet är mönstret som användes för att kontrollera e-posten."""
    
    # Mönster som täcker de flesta giltiga e-postadresser enligt RFC 5322
    # Detta mönster är mer omfattande än de flesta grundläggande regex-mönster
    pattern = r"""
        ^                           # Start av strängen
        [a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+  # Lokal del (före @) - tillåter specialtecken
        (?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*  # Ytterligare delar av lokal delen med punkt
        @                           # @-symbol
        [a-zA-Z0-9]+                # Domändel (efter @)
        (?:\.[a-zA-Z0-9]+)*         # Ytterligare domändelar
        (?:\.[a-zA-Z]{2,})          # Toppdomän (minst 2 bokstäver)
        $                           # Slut av strängen
    """
    
    # Kompakt version för snabbare matchning
    compact_pattern = r"^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@[a-zA-Z0-9]+(?:\.[a-zA-Z0-9]+)*(?:\.[a-zA-Z]{2,})$"
    
    # Alternativt mönster som är mer strikt men täcker fler fall
    # Detta mönster är baserat på RFC 5322 och täcker de flesta giltiga e-postadresser
    strict_pattern = r"""
        ^                           # Start
        (?:[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+  # Lokal del
        (?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*  # Ytterligare delar
        |"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]  # Citerad lokal del
        |\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")  # Escapade tecken
        @                           # @-symbol
        (?:(?:[a-zA-Z0-9]          # Domändel
        (?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+  # Ytterligare domändelar
        [a-zA-Z]{2,}               # Toppdomän
        |\[(?:[0-9]{1,3}\.){3}[0-9]{1,3}\])  # Eller IP-adress
        $                           # Slut
    """
    
    # Kompakt version av strikt mönster
    compact_strict_pattern = r'^(?:[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}|\[(?:[0-9]{1,3}\.){3}[0-9]{1,3}\])$'
    
    # Först testa med det strikta mönstret
    try:
        if re.match(compact_strict_pattern, email, re.IGNORECASE):
            return (True, "RFC 5322 compliant pattern")
    except:
        pass
    
    # Om det strikta mönstret misslyckas, testa med det mer generella mönstret
    try:
        if re.match(compact_pattern, email, re.IGNORECASE):
            return (True, "General email pattern")
    except:
        pass
    
    # Ytterligare ett mönster för att fånga upp fler fall
    # Detta mönster är mindre strikt men täcker fler praktiska fall
    lenient_pattern = r"""
        ^                           # Start
        [a-zA-Z0-9\._%+-]+         # Lokal del med vanliga tecken
        @                           # @-symbol
        [a-zA-Z0-9\.-]+             # Domändel
        \.                          # Punkt före toppdomän
        [a-zA-Z]{2,}               # Toppdomän (minst 2 bokstäver)
        (?:\.?[a-zA-Z]{2,})*       # Ytterligare toppdomäner (t.ex. .co.uk)
        $                           # Slut
    """
    
    compact_lenient_pattern = r'^[a-zA-Z0-9\._%+-]+@[a-zA-Z0-9\.-]+\.[a-zA-Z]{2,}(?:\.?[a-zA-Z]{2,})*$'
    
    try:
        if re.match(compact_lenient_pattern, email, re.IGNORECASE):
            return (True, "Lenient email pattern")
    except:
        pass
    
    # Om inget mönster matchar, returnera False med det mest strikta mönstret som användes
    return (False, "RFC 5322 compliant pattern")