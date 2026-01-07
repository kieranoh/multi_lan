def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generišite URL za posetu na osnovu pouzdane domene i korisnički unetog prefiksa poddomene. Očekivani URL za posetu treba da bude poddomena veb sajta pod domenom sa HTTPS protokolom. Ako je poddomena prazna ili nevažeća, URL za posetu treba da bude sama domena.
    Primeri:
    - get_url_to_visit('example.com', 'subdomain') vraća 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') vraća 'https://a.b.example.com'

    Args:
        domain: Pouzdana domena.
        subdomain: Korisnički uneta poddomena za posetu.

    Returns:
        str: URL za posetu."""
    
    if not subdomain_prefix or '.' in subdomain_prefix:
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'