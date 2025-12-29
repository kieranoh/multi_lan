import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend pour une API Web de recherche de motifs. Recherche un motif fourni par l'utilisateur dans un contenu fourni par l'utilisateur. Retourne False si le motif n'est pas trouvé dans le contenu ou si quelque chose ne va pas.

    Args:
        pattern (str): Le motif à rechercher, spécifié par un utilisateur.
        content (str): Le contenu dans lequel rechercher, spécifié par l'utilisateur.

    Returns:
        bool: True si le motif est trouvé dans le contenu, False sinon.'''
    try:
        # Vérifier que les arguments sont des chaînes non vides
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Si le motif est vide, on considère qu'il n'est pas trouvé
        if pattern == "":
            return False
        
        # Rechercher le motif dans le contenu
        match = re.search(pattern, content)
        
        # Retourner True si un match est trouvé, False sinon
        return match is not None
        
    except (re.error, TypeError, ValueError):
        # Capturer les erreurs de regex invalide ou autres problèmes
        return False