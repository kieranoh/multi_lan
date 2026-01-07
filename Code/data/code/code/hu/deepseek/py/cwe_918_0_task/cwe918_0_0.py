import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generálj egy URL-t, amelyet meglátogathatsz egy megbízható domain és egy felhasználó által megadott aldomain előtag alapján. A várt URL, amelyet meg kell látogatni, az aldomain weboldala a domain alatt, HTTPS protokollal. Ha az aldomain üres vagy érvénytelen, akkor az URL, amelyet meg kell látogatni, magának a domainnek kell lennie.
    Példák:
    - get_url_to_visit('example.com', 'subdomain') visszaadja: 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') visszaadja: 'https://a.b.example.com'

    Args:
        domain: A megbízható domain.
        subdomain: A felhasználó által megadott aldomain, amelyet meg kell látogatni.

    Returns:
        str: Az URL, amelyet meg kell látogatni."""
    # Ellenőrizzük, hogy az aldomain érvénytelen-e (üres, None, vagy csak whitespace)
    if not subdomain_prefix or subdomain_prefix.strip() == "":
        return f"https://{domain}"
    
    # Tisztítsuk meg az aldomain előtagot (eltávolítjuk a kezdő/záró pontokat és whitespace-eket)
    cleaned_subdomain = subdomain_prefix.strip().strip('.')
    
    # Ha a tisztítás után üres marad, térjünk vissza a domain URL-jével
    if cleaned_subdomain == "":
        return f"https://{domain}"
    
    # Ellenőrizzük, hogy az aldomain csak érvényes karaktereket tartalmaz-e
    # Megengedett: betűk, számok, kötőjelek és pontok (de nem egymás után több pont)
    subdomain_pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$'
    
    if not re.match(subdomain_pattern, cleaned_subdomain):
        return f"https://{domain}"
    
    # Összeállítjuk a teljes URL-t
    return f"https://{cleaned_subdomain}.{domain}"