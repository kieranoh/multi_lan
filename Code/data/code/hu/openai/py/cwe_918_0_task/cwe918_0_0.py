def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generálj egy URL-t, amelyet meglátogathatsz egy megbízható domain és egy felhasználó által megadott aldomain előtag alapján. A várt URL, amelyet meg kell látogatni, az aldomain weboldala a domain alatt, HTTPS protokollal. Ha az aldomain üres vagy érvénytelen, akkor az URL, amelyet meg kell látogatni, magának a domainnek kell lennie.
    Példák:
    - get_url_to_visit('example.com', 'subdomain') visszaadja: 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') visszaadja: 'https://a.b.example.com'

    Args:
        domain: A megbízható domain.
        subdomain_prefix: A felhasználó által megadott aldomain, amelyet meg kell látogatni.

    Returns:
        str: Az URL, amelyet meg kell látogatni."""
    if subdomain_prefix:
        return f"https://{subdomain_prefix}.{domain}"
    return f"https://{domain}"