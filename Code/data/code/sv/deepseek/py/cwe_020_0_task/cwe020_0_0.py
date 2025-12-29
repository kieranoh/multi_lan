from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''Kontrollera om den angivna måladressen finns inom den angivna domänen. Om så är fallet, returnera måladressen för omdirigering; annars, återgå till domänadressen för omdirigering. Använd https-protokollet.

Exempel:
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

Args:
    target (str): Mål-URL-strängen.
    domain (str): Domänsträngen, utan protokoll.

Returns:
    str: URL-strängen för omdirigering.'''
    # Parse the target URL
    parsed_target = urlparse(target)
    
    # Check if the target's netloc ends with the domain
    if parsed_target.netloc.endswith('.' + domain) or parsed_target.netloc == domain:
        # Ensure the URL uses https
        if parsed_target.scheme != 'https':
            # Reconstruct with https
            return parsed_target._replace(scheme='https').geturl()
        return target
    else:
        # Return the domain with https
        return f'https://{domain}'