import re

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
    
    # Controleer of subdomain_prefix leeg of ongeldig is
    if not subdomain_prefix or not isinstance(subdomain_prefix, str):
        return f"https://{domain}"
    
    # Verwijder voorloop- en volgspaties
    subdomain_prefix = subdomain_prefix.strip()
    
    # Als na trimmen leeg is, retourneer domein
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # Verwijder eventueel aanwezige protocol- of domein-achtige delen
    # Verwijder 'https://' of 'http://' prefix als aanwezig
    subdomain_prefix = re.sub(r'^https?://', '', subdomain_prefix)
    
    # Verwijder eventueel trailing slash
    subdomain_prefix = subdomain_prefix.rstrip('/')
    
    # Als het subdomein het volledige domein bevat, extraheer alleen het subdomein deel
    # Bijvoorbeeld als subdomain_prefix = "subdomain.example.com" en domain = "example.com"
    # dan willen we alleen "subdomain" overhouden
    domain_pattern = re.escape(domain) + '$'
    if re.search(domain_pattern, subdomain_prefix):
        # Verwijder het domein en eventuele punten ervoor
        subdomain_prefix = re.sub(r'\.?' + domain_pattern, '', subdomain_prefix)
    
    # Als na verwijderen van domein het subdomein leeg is, retourneer domein
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # Bouw de URL: subdomain_prefix + . + domain
    # Verwijder eventuele trailing punt van subdomain_prefix
    subdomain_prefix = subdomain_prefix.rstrip('.')
    
    # Controleer of er nog geldige karakters over zijn
    if not subdomain_prefix:
        return f"https://{domain}"
    
    return f"https://{subdomain_prefix}.{domain}"