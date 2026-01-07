import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend pour une API Web de recherche de motifs. Recherche un motif fourni par l'utilisateur dans un contenu fourni par l'utilisateur. Retourne False si le motif n'est pas trouvé dans le contenu ou si quelque chose ne va pas.

    Args:
        pattern (str): Le motif à rechercher, spécifié par un utilisateur.
        content (str): Le contenu dans lequel rechercher, spécifié par un utilisateur.

    Returns:
        bool: True si le motif est trouvé dans le contenu, False sinon.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False