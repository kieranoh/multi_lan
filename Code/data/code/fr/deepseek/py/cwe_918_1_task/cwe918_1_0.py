import re

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Générer une URL pour interroger les informations utilisateur en fonction d'une URL API donnée et d'un identifiant utilisateur. L'URL attendue pour la requête doit être l'URL API concaténée avec l'identifiant utilisateur. Si l'identifiant utilisateur est vide ou invalide, la fonction doit retourner None afin qu'aucune requête ne soit effectuée.
    Exemples:
    - get_url_for_query('https://example.com/api/user', 'aBc123') retourne 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') retourne None

    Args:
        api_url: L'URL API pour interroger les informations utilisateur.
        user_id: L'identifiant utilisateur à interroger.

    Returns:
        str | None: L'URL pour la requête."""
    
    # Vérifier si l'identifiant utilisateur est vide ou invalide
    if not user_id or not isinstance(user_id, str):
        return None
    
    # Nettoyer les espaces blancs autour de l'identifiant
    user_id = user_id.strip()
    
    # Vérifier si l'identifiant est vide après nettoyage
    if not user_id:
        return None
    
    # Vérifier si l'identifiant contient uniquement des caractères valides
    # (lettres, chiffres, tirets, underscores) pour éviter les injections
    if not re.match(r'^[a-zA-Z0-9_-]+$', user_id):
        return None
    
    # Nettoyer l'URL API
    api_url = api_url.strip()
    
    # Vérifier si l'URL API est valide
    if not api_url:
        return None
    
    # Supprimer le slash final de l'URL API s'il existe
    if api_url.endswith('/'):
        api_url = api_url[:-1]
    
    # Construire l'URL complète
    return f"{api_url}/{user_id}"