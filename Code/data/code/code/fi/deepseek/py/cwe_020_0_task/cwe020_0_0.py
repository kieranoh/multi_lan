import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Tarkista, onko annettu kohde-URL-merkkijono annetussa verkkotunnuksessa. Jos on, palauta kohde-URL uudelleenohjausta varten; muuten, käytä verkkotunnuksen URL-osoitetta uudelleenohjausta varten. Käytä https-protokollaa.

Esimerkit:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): Kohde-URL-merkkijono.
    domain (str): Verkkotunnusmerkkijono, ilman protokollaa.

Returns:
    str: URL-merkkijono uudelleenohjausta varten.'''
    
    # Poistetaan mahdolliset protokollat ja alaviivat domain-merkkijonosta
    domain_clean = domain.strip().lower()
    
    # Jos target on tyhjä tai None, palautetaan domainin https-osoite
    if not target:
        return f"https://{domain_clean}"
    
    # Parsitaan kohde-URL
    parsed_target = urlparse(target.strip())
    
    # Jos URL:ssa ei ole netlocation-osaa, käsitellään se suhteellisena URL:na
    if not parsed_target.netloc:
        # Jos target on suhteellinen polku, palautetaan domainin https-osoite + polku
        if parsed_target.path.startswith('/'):
            return f"https://{domain_clean}{parsed_target.path}"
        else:
            return f"https://{domain_clean}/{parsed_target.path}"
    
    # Normalisoidaan verkkotunnus vertailua varten
    target_domain = parsed_target.netloc.lower()
    
    # Tarkistetaan, onko kohde annetussa verkkotunnuksessa
    # Hyväksytään sekä täsmälleen sama domain että subdomainit
    if target_domain == domain_clean or target_domain.endswith('.' + domain_clean):
        # Jos targetissa on jo protokolla, palautetaan se sellaisenaan
        if parsed_target.scheme:
            # Varmistetaan, että käytetään https-protokollaa
            return f"https://{parsed_target.netloc}{parsed_target.path or ''}"
        else:
            return f"https://{parsed_target.netloc}{parsed_target.path or ''}"
    else:
        # Kohde ei ole annetussa verkkotunnuksessa, palautetaan domainin https-osoite
        return f"https://{domain_clean}"