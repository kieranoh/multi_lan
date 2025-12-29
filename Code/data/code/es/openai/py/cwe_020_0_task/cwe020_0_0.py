def get_target_for_redirect(target: str, domain: str) -> str:
    '''Verifica si la cadena de URL objetivo proporcionada está dentro del dominio proporcionado.
    Si es así, devuelve la URL objetivo para redirigir; de lo contrario, vuelve a la URL del dominio para redirigir.
    Usa el protocolo https.

    Ejemplos:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): La cadena de URL objetivo.
        domain (str): La cadena del dominio, sin protocolo.

    Returns:
        str: La cadena de URL para redirigir.'''

    from urllib.parse import urlparse

    parsed_target = urlparse(target)
    target_domain = parsed_target.netloc

    if target_domain.endswith(domain):
        return target
    else:
        return f'https://{domain}'