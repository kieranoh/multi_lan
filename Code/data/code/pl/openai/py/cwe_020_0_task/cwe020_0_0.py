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
    
    from urllib.parse import urlparse

    parsed_target = urlparse(target)
    target_domain = parsed_target.netloc

    # Check if the target's domain matches the provided domain
    if domain in target_domain:
        return target

    return f'https://{domain}'