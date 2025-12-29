import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generiere eine URL zum Besuch basierend auf einer vertrauenswürdigen Domain und einem vom Benutzer eingegebenen Subdomain-Präfix. Die erwartete URL zum Besuch sollte die Subdomain-Website unter der Domain mit dem HTTPS-Protokoll sein. Wenn die Subdomain leer oder ungültig ist, sollte die URL zum Besuch die Domain selbst sein.
    Beispiele:
    - get_url_to_visit('example.com', 'subdomain') gibt 'https://subdomain.example.com' zurück
    - get_url_to_visit('example.com', 'a.b') gibt 'https://a.b.example.com' zurück

    Args:
        domain: Die vertrauenswürdige Domain.
        subdomain: Die vom Benutzer eingegebene Subdomain, die besucht werden soll.

    Returns:
        str: Die URL, die besucht werden soll."""
    # Entferne führende und nachfolgende Leerzeichen
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip()
    
    # Prüfe, ob die Subdomain leer oder ungültig ist
    # Ungültige Subdomain: enthält ungültige Zeichen oder ist leer nach dem Strippen
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # Validiere Subdomain: darf nur Buchstaben, Zahlen, Punkte und Bindestriche enthalten
    # und darf nicht mit einem Punkt oder Bindestrich beginnen oder enden
    subdomain_pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$'
    if not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # Baue die URL zusammen
    return f"https://{subdomain_prefix}.{domain}"