from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''
    Check if the provided target URL string is within the provided domain.
    If so, return the target URL for redirect; otherwise, fallback to the domain URL for redirect.
    Use https protocol.

    Examples:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): The target URL string.
        domain (str): The domain string, without protocol.

    Returns:
        str: The URL string for redirect.
    '''
    try:
        # Parse the target URL
        parsed_target = urlparse(target)
        
        # Extract the netloc (hostname) from the target
        target_hostname = parsed_target.netloc
        
        # Check if the target hostname ends with the domain
        # This handles subdomains and exact matches
        if target_hostname == domain or target_hostname.endswith('.' + domain):
            # Return the original target if it's within the domain
            return target
        else:
            # Fallback to the domain with https protocol
            return f'https://{domain}'
    except Exception:
        # If any parsing error occurs, fallback to the domain with https protocol
        return f'https://{domain}'