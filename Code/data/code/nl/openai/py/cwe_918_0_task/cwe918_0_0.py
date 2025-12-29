def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Genereer een URL om te bezoeken op basis van een vertrouwd domein en een door de gebruiker ingevoerde subdomeinprefix. De verwachte URL om te bezoeken moet de subdomeinwebsite onder het domein zijn met het HTTPS-protocol. Als het subdomein leeg of ongeldig is, moet de te bezoeken URL het domein zelf zijn.
    Voorbeelden:
    - get_url_to_visit('example.com', 'subdomain') retourneert 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') retourneert 'https://a.b.example.com'

    Args:
        domain: Het vertrouwde domein.
        subdomain_prefix: Het door de gebruiker ingevoerde subdomein om te bezoeken.

    Returns:
        str: De te bezoeken URL."""
    
    if subdomain_prefix and all(part.isalnum() for part in subdomain_prefix.split('.')):
        return f'https://{subdomain_prefix}.{domain}'
    return f'https://{domain}'