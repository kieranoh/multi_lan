def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generirajte URL za posjet temeljen na pouzdanoj domeni i korisnički unesenom prefiksu poddomene. Očekivani URL za posjet trebao bi biti web stranica poddomene pod domenom s HTTPS protokolom. Ako je poddomena prazna ili nevažeća, URL za posjet trebao bi biti sama domena.
    Primjeri:
    - get_url_to_visit('example.com', 'subdomain') vraća 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') vraća 'https://a.b.example.com'

    Args:
        domain: Pouzdana domena.
        subdomain_prefix: Korisnički unesena poddomena za posjet.

    Returns:
        str: URL za posjet."""
    
    if not subdomain_prefix or not isinstance(subdomain_prefix, str) or not all(part.isalnum() or part == '.' for part in subdomain_prefix.split('.')):
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'