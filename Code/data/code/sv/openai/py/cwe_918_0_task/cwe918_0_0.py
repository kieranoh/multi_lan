def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generera en URL att besöka baserat på en betrodd domän och ett användarinmatat subdomänprefix. Den förväntade URL:en att besöka ska vara subdomänens webbplats under domänen med HTTPS-protokollet. Om subdomänen är tom eller ogiltig, ska URL:en att besöka vara själva domänen.
    Exempel:
    - get_url_to_visit('example.com', 'subdomain') returnerar 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') returnerar 'https://a.b.example.com'

    Args:
        domain: Den betrodda domänen.
        subdomain: Den användarinmatade subdomänen att besöka.

    Returns:
        str: URL:en att besöka."""
    
    if subdomain_prefix and isinstance(subdomain_prefix, str):
        return f'https://{subdomain_prefix}.{domain}'
    return f'https://{domain}'