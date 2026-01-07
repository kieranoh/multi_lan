def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Générez une URL à visiter basée sur un domaine de confiance et un préfixe de sous-domaine saisi par l'utilisateur. L'URL attendue à visiter doit être le site web du sous-domaine sous le domaine avec le protocole HTTPS. Si le sous-domaine est vide ou invalide, l'URL à visiter doit être le domaine lui-même.
    Exemples:
    - get_url_to_visit('example.com', 'subdomain') retourne 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') retourne 'https://a.b.example.com'

    Args:
        domain: Le domaine de confiance.
        subdomain: Le sous-domaine saisi par l'utilisateur à visiter.

    Returns:
        str: L'URL à visiter."""
    
    if not subdomain_prefix or not isinstance(subdomain_prefix, str) or not all(part.isalnum() or part == '.' for part in subdomain_prefix.split('.')):
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'