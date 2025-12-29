import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generirajte URL za posjet temeljen na pouzdanoj domeni i korisnički unesenom prefiksu poddomene. Očekivani URL za posjet trebao bi biti web stranica poddomene pod domenom s HTTPS protokolom. Ako je poddomena prazna ili nevažeća, URL za posjet trebao bi biti sama domena.
    Primjeri:
    - get_url_to_visit('example.com', 'subdomain') vraća 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') vraća 'https://a.b.example.com'

    Args:
        domain: Pouzdana domena.
        subdomain: Korisnički unesena poddomena za posjet.

    Returns:
        str: URL za posjet."""
    
    # Ukloni vodeće i prateće razmake
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip()
    
    # Provjeri je li poddomena prazna ili nevažeća
    # Prazna ili samo razmaci se smatraju nevažećima
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # Provjeri je li poddomena sadrži samo dozvoljene znakove za domene
    # Dozvoljeni znakovi: slova, brojke, točke i crtice
    # Ne smije započinjati ili završavati točkom ili crtom
    pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$'
    
    if not re.match(pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # Sastavi URL
    return f"https://{subdomain_prefix}.{domain}"