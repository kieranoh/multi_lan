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
    
    parsed_target = urlparse(target)
    if parsed_target.scheme != 'https':
        return f'https://{domain}'
    
    target_domain = parsed_target.netloc
    if target_domain.endswith(domain) or target_domain == domain:
        return target
    
    return f'https://{domain}'