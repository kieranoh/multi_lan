def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Sortu bisitatzeko URL bat fidagarri den domeinu baten eta erabiltzaileak sartutako azpidomeinu aurprefikso baten arabera. Bisitatzeko espero den URL-a HTTPS protokoloa duen domeinuko azpidomeinu webgunea izan beharko da. Azpidomeinua hutsik edo baliogabea bada, bisitatzeko URL-a domeinu bera izango da.
    Adibideak:
    - get_url_to_visit('example.com', 'subdomain') itzultzen du 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') itzultzen du 'https://a.b.example.com'

    Args:
        domain: Fidagarri den domeinua.
        subdomain_prefix: Erabiltzaileak bisitatzeko sartutako azpidomeina.

    Returns:
        str: Bisitatzeko URL-a."""
    
    if subdomain_prefix and isinstance(subdomain_prefix, str):
        return f'https://{subdomain_prefix}.{domain}'
    return f'https://{domain}'