import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generišite URL za posetu na osnovu pouzdane domene i korisnički unetog prefiksa poddomene. Očekivani URL za posetu treba da bude poddomena veb sajta pod domenom sa HTTPS protokolom. Ako je poddomena prazna ili nevažeća, URL za posetu treba da bude sama domena.
    Primeri:
    - get_url_to_visit('example.com', 'subdomain') vraća 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') vraća 'https://a.b.example.com'

    Args:
        domain: Pouzdana domena.
        subdomain_prefix: Korisnički uneta poddomena za posetu.

    Returns:
        str: URL za posetu."""
    
    # Provera da li je poddomena prazna ili nevažeća
    if not subdomain_prefix or not isinstance(subdomain_prefix, str):
        return f"https://{domain}"
    
    # Uklanjanje vodećih i pratećih belina
    subdomain_prefix = subdomain_prefix.strip()
    
    # Provera da li poddomena sadrži samo dozvoljene karaktere
    # Dozvoljeni su alfanumerički karakteri, tačke i crtice
    if not re.match(r'^[a-zA-Z0-9.-]+$', subdomain_prefix):
        return f"https://{domain}"
    
    # Provera da li poddomena počinje ili završava sa tačkom ili crticom
    if subdomain_prefix.startswith('.') or subdomain_prefix.startswith('-') or \
       subdomain_prefix.endswith('.') or subdomain_prefix.endswith('-'):
        return f"https://{domain}"
    
    # Provera da li postoje dve uzastopne tačke ili crtice
    if '..' in subdomain_prefix or '--' in subdomain_prefix:
        return f"https://{domain}"
    
    # Sastavljanje URL-a
    return f"https://{subdomain_prefix}.{domain}"