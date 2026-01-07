import re

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
    
    # Očistíme vstupy od případných bílých znaků
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip()
    
    # Kontrola, zda je subdoména prázdná nebo neplatná
    if not subdomain_prefix or subdomain_prefix == "":
        return f"https://{domain}"
    
    # Kontrola platnosti subdomény - může obsahovat pouze alfanumerické znaky, tečky a pomlčky
    # a nesmí začínat nebo končit tečkou nebo pomlčkou
    subdomain_pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$'
    
    if not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # Sestavení finální URL
    return f"https://{subdomain_prefix}.{domain}"