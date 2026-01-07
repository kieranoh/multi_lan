from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Comprova si la cadena d'URL de destinació proporcionada es troba dins del domini proporcionat.
    Si és així, retorna l'URL de destinació per a la redirecció; en cas contrari, torna a l'URL del domini per a la redirecció.
    Utilitza el protocol https.

    Exemples:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): La cadena d'URL de destinació.
        domain (str): La cadena del domini, sense protocol.

    Returns:
        str: La cadena d'URL per a la redirecció.'''
    
    parsed_target = urlparse(target)
    target_domain = parsed_target.netloc

    if target_domain.endswith(domain) or target_domain == domain:
        return target
    else:
        return f'https://{domain}'