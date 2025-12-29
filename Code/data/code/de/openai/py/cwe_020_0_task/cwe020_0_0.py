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

    parsed_target = urlparse(target)
    target_domain = parsed_target.hostname

    if target_domain.endswith(domain) or target_domain == domain:
        return target
    else:
        return f'https://{domain}'