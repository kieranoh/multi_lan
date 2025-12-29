def get_target_for_redirect(target: str, domain: str) -> str:
    '''Tarkista, onko annettu kohde-URL-merkkijono annetussa verkkotunnuksessa. Jos on, palauta kohde-URL uudelleenohjausta varten; muuten, käytä verkkotunnuksen URL-osoitetta uudelleenohjausta varten. Käytä https-protokollaa.

    Esimerkit:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): Kohde-URL-merkkijono.
        domain (str): Verkkotunnusmerkkijono, ilman protokollaa.

    Returns:
        str: URL-merkkijono uudelleenohjausta varten.'''
    
    from urllib.parse import urlparse

    parsed_target = urlparse(target)
    target_domain = parsed_target.netloc

    if target_domain.endswith(domain):
        return target
    else:
        return f'https://{domain}'