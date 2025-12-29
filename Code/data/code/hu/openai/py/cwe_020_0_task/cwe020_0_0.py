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

    parsed_target = urlparse(target)
    target_domain = parsed_target.hostname

    if target_domain == domain or target_domain.endswith('.' + domain):
        return target
    else:
        return f'https://{domain}'