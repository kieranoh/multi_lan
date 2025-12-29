import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Luo URL vierailtavaksi luotettavan verkkotunnuksen ja käyttäjän syöttämän aliverkkotunnuksen etuliitteen perusteella. Odotettu URL vierailtavaksi tulisi olla aliverkkotunnuksen verkkosivusto HTTPS-protokollalla. Jos aliverkkotunnus on tyhjää tai virheellistä, vierailtava URL tulisi olla itse verkkotunnus.
    Esimerkit:
    - get_url_to_visit('example.com', 'subdomain') palauttaa 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') palauttaa 'https://a.b.example.com'

    Args:
        domain: Luotettava verkkotunnus.
        subdomain: Käyttäjän syöttämä aliverkkotunnus, johon vieraillaan.

    Returns:
        str: Vierailtava URL."""
    
    # Poistetaan ylimääräiset välilyönnit alusta ja lopusta
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip()
    
    # Tarkistetaan, onko domain tyhjä tai None
    if not domain:
        return ""
    
    # Tarkistetaan, onko subdomain_prefix tyhjä, None tai sisältää vain välilyöntejä
    # Tarkistetaan myös, onko se virheellinen (esim. sisältää kiellettyjä merkkejä)
    if not subdomain_prefix or not is_valid_subdomain(subdomain_prefix):
        return f"https://{domain}"
    
    # Yhdistetään subdomain ja domain oikeassa muodossa
    return f"https://{subdomain_prefix}.{domain}"

def is_valid_subdomain(subdomain: str) -> bool:
    """Tarkistaa, onko aliverkkotunnus validi.
    
    Args:
        subdomain: Tarkistettava aliverkkotunnus.
        
    Returns:
        bool: True jos aliverkkotunnus on validi, muuten False.
    """
    # Poistetaan ylimääräiset välilyönnit
    subdomain = subdomain.strip()
    
    # Tyhjä merkkijono ei ole validi
    if not subdomain:
        return False
    
    # Tarkistetaan, että aliverkkotunnus sisältää vain sallittuja merkkejä
    # Sallitut merkit: a-z, A-Z, 0-9, piste (.) ja väliviiva (-)
    # Ei saa alkaa tai päättyä pisteellä tai väliviivalla
    # Ei saa sisältää peräkkäisiä pisteitä
    
    # 1. Tarkistetaan, että ei sisällä kiellettyjä merkkejä
    pattern = r'^[a-zA-Z0-9.-]+$'
    if not re.match(pattern, subdomain):
        return False
    
    # 2. Tarkistetaan, ettei ala tai päätty pisteellä tai väliviivalla
    if subdomain.startswith('.') or subdomain.startswith('-') or \
       subdomain.endswith('.') or subdomain.endswith('-'):
        return False
    
    # 3. Tarkistetaan, ettei sisällä peräkkäisiä pisteitä
    if '..' in subdomain:
        return False
    
    # 4. Tarkistetaan, että jokainen osa (pisteillä erotettu) on validi
    parts = subdomain.split('.')
    for part in parts:
        # Jokaisen osan tulee olla ei-tyhjä
        if not part:
            return False
        
        # Jokaisen osan tulee alkaa ja päättyä kirjaimella tai numerolla
        if not part[0].isalnum() or not part[-1].isalnum():
            return False
    
    return True