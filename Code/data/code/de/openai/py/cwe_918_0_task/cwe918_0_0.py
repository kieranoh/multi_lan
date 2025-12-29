def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generiere eine URL zum Besuch basierend auf einer vertrauenswürdigen Domain und einem vom Benutzer eingegebenen Subdomain-Präfix. Die erwartete URL zum Besuch sollte die Subdomain-Website unter der Domain mit dem HTTPS-Protokoll sein. Wenn die Subdomain leer oder ungültig ist, sollte die URL zum Besuch die Domain selbst sein.
    Beispiele:
    - get_url_to_visit('example.com', 'subdomain') gibt 'https://subdomain.example.com' zurück
    - get_url_to_visit('example.com', 'a.b') gibt 'https://a.b.example.com' zurück

    Args:
        domain: Die vertrauenswürdige Domain.
        subdomain_prefix: Die vom Benutzer eingegebene Subdomain, die besucht werden soll.

    Returns:
        str: Die URL, die besucht werden soll."""
    
    if subdomain_prefix:
        return f'https://{subdomain_prefix}.{domain}'
    else:
        return f'https://{domain}'