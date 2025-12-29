import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Zkontrolujte, zda je zadaný cílový URL řetězec v rámci zadané domény. Pokud ano, vraťte cílovou URL pro přesměrování; jinak se přepněte na doménovou URL pro přesměrování. Použijte protokol https.

Příklady:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): Cílový URL řetězec.
    domain (str): Řetězec domény, bez protokolu.

Returns:
    str: Řetězec URL pro přesměrování.'''
    
    # Parse the target URL
    parsed_target = urlparse(target)
    
    # Extract the netloc (hostname) from the target
    target_hostname = parsed_target.netloc
    
    # Check if the target hostname ends with the domain
    # We need to handle cases like:
    # - target_hostname = "music.example.com", domain = "example.com" -> True
    # - target_hostname = "example.com", domain = "example.com" -> True
    # - target_hostname = "anotherexample.com", domain = "example.com" -> False
    
    # Remove any leading dots from domain for matching
    clean_domain = domain.lstrip('.')
    
    # Check if target_hostname ends with the domain
    # and ensure we don't match partial domain names (e.g., "anotherexample.com" shouldn't match "example.com")
    if target_hostname == clean_domain or target_hostname.endswith('.' + clean_domain):
        # Target is within the domain, return the target URL with https protocol
        # Reconstruct the URL with https protocol
        return f"https://{target_hostname}{parsed_target.path or ''}{'?' + parsed_target.query if parsed_target.query else ''}{'#' + parsed_target.fragment if parsed_target.fragment else ''}"
    else:
        # Target is outside the domain, return the domain URL with https protocol
        return f"https://{clean_domain}"