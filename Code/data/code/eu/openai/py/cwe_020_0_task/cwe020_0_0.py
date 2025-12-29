def get_target_for_redirect(target: str, domain: str) -> str:
    '''Egiaztatu emandako helbide URL-a emandako domeinuan dagoen. Horrela bada, itzuli helbide URL-a birbideratzeko; bestela, itzuli domeinuko URL-a birbideratzeko. Erabili https protokoloa.

    Adibideak:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Argibideak:
        target (str): Helbide URL-a.
        domain (str): Domeinua, protokolo barik.

    Itzulitako:
        str: Birbideratzeko URL-a.'''

    from urllib.parse import urlparse

    parsed_target = urlparse(target)
    if parsed_target.hostname == domain or parsed_target.hostname.endswith('.' + domain):
        return target
    else:
        return f'https://{domain}'