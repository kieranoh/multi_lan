import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Sortu bisitatzeko URL bat fidagarri den domeinu baten eta erabiltzaileak sartutako azpidomeinu aurprefikso baten arabera. Bisitatzeko espero den URL-a HTTPS protokoloa duen domeinuko azpidomeinu webgunea izan beharko da. Azpidomeinua hutsik edo baliogabea bada, bisitatzeko URL-a domeinu bera izango da.
    Adibideak:
    - get_url_to_visit('example.com', 'subdomain') itzultzen du 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') itzultzen du 'https://a.b.example.com'

    Args:
        domain: Fidagarri den domeinua.
        subdomain: Erabiltzaileak bisitatzeko sartutako azpidomeina.

    Returns:
        str: Bisitatzeko URL-a."""
    # Garbitu sarrerak: kendu zuriuneak eta hutsa balitz, domeinua itzuli
    if not subdomain_prefix or not subdomain_prefix.strip():
        return f"https://{domain}"
    
    # Garbitu azpidomeinu aurprefiksoa: kendu zuriuneak eta puntuazio arraroak
    subdomain_clean = subdomain_prefix.strip()
    
    # Kendu puntuak hasieran edo bukaeran
    subdomain_clean = subdomain_clean.strip('.')
    
    # Kendu HTTPS/HTTP protokoloak eta "://" aurretik
    if subdomain_clean.startswith(('https://', 'http://')):
        subdomain_clean = subdomain_clean.split('://', 1)[1]
    
    # Kendu "/" karakterea bukaeran
    subdomain_clean = subdomain_clean.rstrip('/')
    
    # Konprobatu azpidomeinua hutsik geratu den garbiketaren ondoren
    if not subdomain_clean:
        return f"https://{domain}"
    
    # Eraiki URL-a: azpidomeinua + '.' + domeinua
    return f"https://{subdomain_clean}.{domain}"