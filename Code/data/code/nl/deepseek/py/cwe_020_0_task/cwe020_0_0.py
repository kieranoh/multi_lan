import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Controleer of de opgegeven doel-URL-string binnen het opgegeven domein valt.
Als dat zo is, retourneer dan de doel-URL voor omleiding; anders, val terug op de domein-URL voor omleiding.
Gebruik het https-protocol.

Voorbeelden:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): De doel-URL-string.
    domain (str): De domeinstring, zonder protocol.

Returns:
    str: De URL-string voor omleiding.'''
    # Parse de target URL
    parsed_target = urlparse(target)
    
    # Controleer of het netloc eindigt met het opgegeven domein
    # Dit behandelt subdomeinen en exacte domein matches
    if parsed_target.netloc.endswith('.' + domain) or parsed_target.netloc == domain:
        # Als de target al https gebruikt, retourneer deze direct
        if parsed_target.scheme == 'https':
            return target
        # Als de target een ander protocol gebruikt, converteer naar https
        else:
            # Reconstruct URL met https protocol
            return f"https://{parsed_target.netloc}{parsed_target.path}" + (f"?{parsed_target.query}" if parsed_target.query else "")
    else:
        # Val terug op het domein met https protocol
        return f"https://{domain}"