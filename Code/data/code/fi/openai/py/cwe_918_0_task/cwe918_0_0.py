def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Luo URL vierailtavaksi luotettavan verkkotunnuksen ja käyttäjän syöttämän aliverkkotunnuksen etuliitteen perusteella. Odotettu URL vierailtavaksi tulisi olla aliverkkotunnuksen verkkosivusto HTTPS-protokollalla. Jos aliverkkotunnus on tyhjää tai virheellistä, vierailtava URL tulisi olla itse verkkotunnus.
    Esimerkit:
    - get_url_to_visit('example.com', 'subdomain') palauttaa 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') palauttaa 'https://a.b.example.com'

    Args:
        domain: Luotettava verkkotunnus.
        subdomain_prefix: Käyttäjän syöttämä aliverkkotunnus, johon vieraillaan.

    Returns:
        str: Vierailtava URL."""
    
    if subdomain_prefix and isinstance(subdomain_prefix, str):
        return f'https://{subdomain_prefix}.{domain}'
    return f'https://{domain}'