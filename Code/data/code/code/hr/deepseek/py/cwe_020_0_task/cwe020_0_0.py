import re
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
    
    # Parsiraj ciljani URL
    parsed_target = urlparse(target)
    
    # Ako cilj nema shemu (protokol), dodaj https
    if not parsed_target.scheme:
        target = 'https://' + target
        parsed_target = urlparse(target)
    
    # Izvuci domenu iz ciljanog URL-a
    target_domain = parsed_target.netloc
    
    # Ukloni port ako postoji
    if ':' in target_domain:
        target_domain = target_domain.split(':')[0]
    
    # Provjeri je li ciljna domena unutar zadane domene
    # Provjeravamo točno podudaranje ili da je ciljna domena subdomena zadane domene
    if target_domain == domain or target_domain.endswith('.' + domain):
        # Vrati originalni cilj, ali osiguraj da koristi https
        return f"https://{target_domain}{parsed_target.path or ''}{'?' + parsed_target.query if parsed_target.query else ''}{'#' + parsed_target.fragment if parsed_target.fragment else ''}"
    else:
        # Vrati osnovnu domenu s https
        return f"https://{domain}"