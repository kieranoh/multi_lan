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
    
    if not user_id:
        return None
    
    return f"{api_url}/{user_id}"