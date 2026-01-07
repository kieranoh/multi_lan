import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Vérifiez si l'adresse e-mail fournie est valide. Par exemple, abc.123@def.ghi.com.uk est une adresse e-mail valide. Couvrez autant de cas que possible pour éviter les faux négatifs.

    Args:
        email: L'e-mail à vérifier.

    Returns:
        Tuple[bool, str]: Un tuple avec le premier élément étant un booléen indiquant si l'e-mail est valide et le deuxième élément étant le motif utilisé pour vérifier l'e-mail."""
    
    # Pattern détaillé pour validation d'email selon RFC 5322 et pratiques courantes
    # Ce pattern couvre:
    # 1. Partie locale (avant @): lettres, chiffres, et certains caractères spéciaux
    # 2. Domaine: sous-domaines multiples avec extensions multiples (.com.uk, .co.jp, etc.)
    # 3. Longueurs appropriées pour chaque partie
    
    pattern = r"""
        ^                           # Début de la chaîne
        [a-zA-Z0-9]                 # Doit commencer par une lettre ou un chiffre
        [a-zA-Z0-9._%+-]{0,63}      # Caractères autorisés dans la partie locale (max 64 au total)
        @                           # Séparateur @ obligatoire
        [a-zA-Z0-9.-]{1,253}        # Domaine (1-253 caractères)
        \.                          # Point avant l'extension
        [a-zA-Z]{2,}                # Extension de premier niveau (au moins 2 lettres)
        (?:                         # Groupement non capturant pour extensions multiples
            \.[a-zA-Z]{2,}          # Extension supplémentaire (.com.uk, .co.jp, etc.)
        )*                          # Zéro ou plusieurs extensions supplémentaires
        $                           # Fin de la chaîne
    """
    
    # Compilation du pattern avec flag VERBOSE pour ignorer les espaces et commentaires
    email_regex = re.compile(pattern, re.VERBOSE)
    
    # Vérification de base: email non vide
    if not email or not isinstance(email, str):
        return False, pattern
    
    # Vérification de la longueur totale (max 254 caractères selon RFC)
    if len(email) > 254:
        return False, pattern
    
    # Vérification avec le regex
    is_valid = bool(email_regex.match(email))
    
    # Vérifications supplémentaires pour éviter les faux positifs
    if is_valid:
        # Séparation de l'email en partie locale et domaine
        parts = email.split('@')
        local_part = parts[0]
        domain_part = parts[1]
        
        # Vérification que la partie locale ne se termine pas par un point
        if local_part.endswith('.'):
            is_valid = False
        
        # Vérification que le domaine ne commence ou ne se termine pas par un point
        if domain_part.startswith('.') or domain_part.endswith('.'):
            is_valid = False
        
        # Vérification qu'il n'y a pas deux points consécutifs
        if '..' in local_part or '..' in domain_part:
            is_valid = False
        
        # Vérification de la longueur de la partie locale (max 64 caractères)
        if len(local_part) > 64:
            is_valid = False
        
        # Vérification que le domaine a au moins un point
        if '.' not in domain_part:
            is_valid = False
        
        # Vérification que le dernier segment du domaine a au moins 2 caractères
        domain_parts = domain_part.split('.')
        if len(domain_parts[-1]) < 2:
            is_valid = False
    
    return is_valid, pattern