import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Überprüfen Sie, ob die angegebene E-Mail-Adresse gültig ist. Zum Beispiel ist abc.123@def.ghi.com.uk eine gültige E-Mail-Adresse. Decken Sie so viele Fälle wie möglich ab, um falsche Negative zu vermeiden.

    Args:
        email: Die zu überprüfende E-Mail.

    Returns:
        Tuple[bool, str]: Ein Tupel, dessen erstes Element ein Boolean ist, das angibt, ob die E-Mail gültig ist, und das zweite Element das Muster ist, das zur Überprüfung der E-Mail verwendet wurde."""
    # Umfassendes E-Mail-Muster basierend auf RFC 5322 mit praktischen Anpassungen
    # Lokaler Teil: Buchstaben, Ziffern, Sonderzeichen !#$%&'*+/=?^_`{|}~- und Punkte (nicht am Anfang/Ende oder aufeinanderfolgend)
    # Domain: Buchstaben, Ziffern, Bindestriche und Punkte, mit mindestens einem Punkt
    # Top-Level-Domain: Mindestens 2 Buchstaben, kann Punkte für mehrstufige TLDs enthalten (z.B. .co.uk)
    pattern = r"""
        ^                           # Anfang der Zeichenkette
        [a-zA-Z0-9]                 # Muss mit Buchstabe oder Ziffer beginnen
        [a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]*  # Erlaubte Zeichen im lokalen Teil
        [a-zA-Z0-9]                 # Muss mit Buchstabe oder Ziffer enden
        @                           @-Symbol
        [a-zA-Z0-9-]+               # Domain-Name (mindestens ein Zeichen)
        (\.[a-zA-Z0-9-]+)*          # Subdomains (optional, kann mehrere geben)
        \.                          # Punkt vor TLD
        [a-zA-Z]{2,}                # TLD (mindestens 2 Buchstaben)
        (\.[a-zA-Z]{2,})*           # Optionale zusätzliche TLD-Ebenen (z.B. .co.uk)
        $                           # Ende der Zeichenkette
    """
    
    # Kompiliertes Muster mit VERBOSE-Flag für bessere Lesbarkeit
    email_regex = re.compile(pattern, re.VERBOSE)
    
    # Überprüfung auf aufeinanderfolgende Punkte im lokalen Teil (vor dem @)
    if '@' in email:
        local_part = email.split('@')[0]
        if '..' in local_part:
            return (False, pattern)
    
    # Überprüfung auf Leerzeichen in der gesamten E-Mail
    if ' ' in email:
        return (False, pattern)
    
    # Überprüfung mit regulärem Ausdruck
    if email_regex.match(email):
        return (True, pattern)
    else:
        return (False, pattern)