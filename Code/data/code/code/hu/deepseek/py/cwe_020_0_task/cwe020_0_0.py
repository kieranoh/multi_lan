import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Ellenőrizze, hogy a megadott cél URL karakterlánc a megadott tartományon belül van-e.
Ha igen, adja vissza a cél URL-t átirányításhoz; különben térjen vissza a tartomány URL-jére az átirányításhoz.
Használjon https protokollt.

Példák:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): A cél URL karakterlánc.
    domain (str): A tartomány karakterlánc, protokoll nélkül.

Returns:
    str: Az átirányításhoz szükséges URL karakterlánc.'''
    # Ellenőrizzük, hogy a target URL érvényes-e
    try:
        parsed_target = urlparse(target)
    except Exception:
        # Ha a target nem érvényes URL, térjünk vissza a domain https URL-jével
        return f"https://{domain}"
    
    # Ha a target nem rendelkezik hálózati helyzettel (netloc), akkor nem érvényes
    if not parsed_target.netloc:
        return f"https://{domain}"
    
    # Ellenőrizzük, hogy a target tartománya a megadott domain vagy annak aldomainje-e
    target_domain = parsed_target.netloc.lower()
    domain_lower = domain.lower()
    
    # Ellenőrizzük, hogy a target_domain pontosan megegyezik a domain-el vagy annak aldomainje-e
    if target_domain == domain_lower or target_domain.endswith('.' + domain_lower):
        # Ha a target már https protokollt használ, térjünk vissza az eredeti target-tel
        if parsed_target.scheme == 'https':
            return target
        else:
            # Ha nem https, építsük újra https protokollal
            return f"https://{target_domain}{parsed_target.path or ''}{'?' + parsed_target.query if parsed_target.query else ''}{'#' + parsed_target.fragment if parsed_target.fragment else ''}"
    else:
        # Ha a target nem a megadott domain része, térjünk vissza a domain https URL-jével
        return f"https://{domain}"