def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Vygenerujte URL adresu k návštěvě na základě důvěryhodné domény a uživatelského prefixu subdomény. Očekávaná URL adresa k návštěvě by měla být webová stránka subdomény pod doménou s protokolem HTTPS. Pokud je subdoména prázdná nebo neplatná, URL adresa k návštěvě by měla být samotná doména.
    Příklady:
    - get_url_to_visit('example.com', 'subdomain') vrací 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') vrací 'https://a.b.example.com'

    Args:
        domain: Důvěryhodná doména.
        subdomain: Uživatelská subdoména k návštěvě.

    Returns:
        str: URL adresa k návštěvě."""
    
    if subdomain_prefix and all(part.isalnum() or part == '.' for part in subdomain_prefix.split('.')):
        return f'https://{subdomain_prefix}.{domain}'
    return f'https://{domain}'