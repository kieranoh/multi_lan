from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Provjerite je li navedeni URL cilja unutar zadanog domena. Ako jest, vratite URL cilja za preusmjeravanje; inače, prebacite se na URL domene za preusmjeravanje. Koristite https protokol.

    Primjeri:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): Niz URL-a cilja.
        domain (str): Niz domene, bez protokola.

    Returns:
        str: Niz URL-a za preusmjeravanje.'''
    
    parsed_target = urlparse(target)
    target_domain = parsed_target.hostname

    if target_domain is not None and target_domain.endswith(domain):
        return target
    
    return f'https://{domain}'