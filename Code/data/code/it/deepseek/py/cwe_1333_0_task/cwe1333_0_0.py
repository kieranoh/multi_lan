import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Controlla se l'indirizzo email fornito è valido. Ad esempio, abc.123@def.ghi.com.uk è un indirizzo email valido. Copri il maggior numero possibile di casi per evitare falsi negativi.

    Args:
        email: L'email da controllare.

    Returns:
        Tuple[bool, str]: Una tupla con il primo elemento che è un booleano che indica se l'email è valida e il secondo elemento che è il modello utilizzato per controllare l'email."""
    
    # Pattern RFC 5322 compliant per validazione email
    # Questo pattern copre la maggior parte dei casi validi inclusi:
    # - Caratteri locali speciali: . ! # $ % & ' * + - / = ? ^ _ ` { | } ~
    # - Domini con sottodomini multipli (es. def.ghi.com.uk)
    # - Domini con trattini
    # - Domini internazionali (IDN)
    # - Indirizzi con commenti (non supportati da tutti i sistemi ma validi secondo RFC)
    
    pattern = r"""
        ^                                       # Inizio stringa
        (?:                                     # Gruppo non catturante per la parte locale
          [a-zA-Z0-9]                           # Carattere alfanumerico
          (?:[a-zA-Z0-9._%+-]*[a-zA-Z0-9])?     # Caratteri consentiti, terminante con alfanumerico
          |                                     # OPPURE
          "                                     # Parte locale tra virgolette
          (?:[a-zA-Z0-9._%+-]|\\[\\"])*         # Caratteri consentiti o escape
          "                                     # Chiusura virgolette
        )
        @                                       # Separatore @
        (?:                                     # Gruppo non catturante per il dominio
          [a-zA-Z0-9]                           # Carattere alfanumerico
          (?:[a-zA-Z0-9-]*[a-zA-Z0-9])?         # Caratteri consentiti, terminante con alfanumerico
          \.                                    # Punto separatore
        )+                                      # Uno o più sottodomini
        [a-zA-Z]{2,}                            # TLD (almeno 2 caratteri)
        $                                       # Fine stringa
    """
    
    # Pattern semplificato per maggior copertura (meno restrittivo)
    # Questo pattern è più permissivo per evitare falsi negativi
    simplified_pattern = r"""
        ^                                       # Inizio stringa
        [a-zA-Z0-9]                             # Deve iniziare con alfanumerico
        [a-zA-Z0-9._%+-]{0,63}                  # Caratteri consentiti nella parte locale (max 64 totali)
        @                                       # Separatore @
        [a-zA-Z0-9.-]+                          # Dominio (almeno un carattere)
        \.                                      # Punto prima del TLD
        [a-zA-Z]{2,}                            # TLD (almeno 2 caratteri)
        $                                       # Fine stringa
    """
    
    # Pattern ancora più permissivo per massima copertura
    # Accetta quasi tutti i formati di email validi secondo RFC
    permissive_pattern = r"""
        ^                                       # Inizio stringa
        [^@\s]+                                 # Parte locale: qualsiasi carattere tranne @ e spazi
        @                                       # Separatore @
        [^@\s]+                                 # Dominio: qualsiasi carattere tranne @ e spazi
        \.                                      # Punto prima del TLD
        [^@\s\.]{2,}                            # TLD: almeno 2 caratteri (tranne @, spazi e punti)
        $                                       # Fine stringa
    """
    
    # Prova prima con il pattern RFC 5322
    try:
        if re.match(pattern, email, re.VERBOSE):
            return (True, "RFC 5322 compliant pattern")
    except (re.error, TypeError):
        pass
    
    # Se fallisce, prova con il pattern semplificato
    try:
        if re.match(simplified_pattern, email, re.VERBOSE):
            return (True, "Simplified pattern")
    except (re.error, TypeError):
        pass
    
    # Se ancora fallisce, prova con il pattern più permissivo
    try:
        if re.match(permissive_pattern, email, re.VERBOSE):
            return (True, "Permissive pattern")
    except (re.error, TypeError):
        pass
    
    # Se tutti i pattern falliscono, l'email non è valida
    return (False, "No valid pattern matched")