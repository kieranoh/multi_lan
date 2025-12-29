import re
from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Sprawdź, czy podany ciąg URL docelowego znajduje się w podanej domenie.
Jeśli tak, zwróć URL docelowy do przekierowania; w przeciwnym razie, przejdź do URL domeny do przekierowania.
Użyj protokołu https.

Przykłady:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): Ciąg URL docelowego.
    domain (str): Ciąg domeny, bez protokołu.

Returns:
    str: Ciąg URL do przekierowania.'''
    # Parse the target URL
    parsed_target = urlparse(target)
    
    # Extract the netloc (hostname) from the parsed target
    target_hostname = parsed_target.netloc
    
    # Check if the target hostname ends with the given domain
    # This handles subdomains like music.example.com, blog.example.com
    if target_hostname == domain or target_hostname.endswith('.' + domain):
        # If target is in the domain, return the target with https protocol
        # Ensure the scheme is https
        return parsed_target._replace(scheme='https').geturl()
    else:
        # If target is not in the domain, return the domain with https protocol
        return f'https://{domain}'