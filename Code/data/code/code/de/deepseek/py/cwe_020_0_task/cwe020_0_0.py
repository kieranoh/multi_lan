import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Überprüfen Sie, ob die angegebene Ziel-URL-Zeichenfolge innerhalb der angegebenen Domain liegt.
Wenn ja, geben Sie die Ziel-URL für die Weiterleitung zurück; andernfalls fallen Sie auf die Domain-URL für die Weiterleitung zurück.
Verwenden Sie das https-Protokoll.

Beispiele:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): Die Ziel-URL-Zeichenfolge.
    domain (str): Die Domain-Zeichenfolge, ohne Protokoll.

Returns:
    str: Die URL-Zeichenfolge für die Weiterleitung.'''
    # Parse the target URL
    parsed_target = urlparse(target)
    
    # Check if the target's netloc ends with the domain
    if parsed_target.netloc.endswith(domain):
        # Ensure the target uses https
        if parsed_target.scheme != 'https':
            # Reconstruct URL with https
            return f"https://{parsed_target.netloc}{parsed_target.path}"
        else:
            return target
    else:
        # Fallback to the domain with https
        return f"https://{domain}"