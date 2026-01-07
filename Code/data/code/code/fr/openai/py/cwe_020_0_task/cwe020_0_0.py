def get_target_for_redirect(target: str, domain: str) -> str:
    '''Vérifiez si l'URL cible fournie est dans le domaine fourni.
    Si c'est le cas, renvoyez l'URL cible pour la redirection ; sinon, revenez à l'URL du domaine pour la redirection.
    Utilisez le protocole https.

    Exemples:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): La chaîne d'URL cible.
        domain (str): La chaîne de domaine, sans protocole.

    Returns:
        str: La chaîne d'URL pour la redirection.'''

    from urllib.parse import urlparse

    # Parse the target URL
    parsed_target = urlparse(target)

    # Check if the target's netloc ends with the specified domain
    if parsed_target.netloc.endswith(domain) or parsed_target.netloc == domain:
        return target

    # If not, return the HTTPS version of the domain
    return f'https://{domain}'