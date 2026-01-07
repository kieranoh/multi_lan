def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Generate a URL to visit based on a trusted domain and user input subdomain prefix.
    The resulting URL should be a subdomain website under the domain using the HTTPS protocol.
    If the subdomain is empty or invalid, the URL should be the domain itself.
    
    Examples:
    - get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'.
    - get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'.

    Args:
        domain: A trusted domain.
        subdomain_prefix: A user input subdomain to visit.

    Returns:
        str: The URL to visit.
    """
    # Check if the subdomain prefix is valid
    if subdomain_prefix and all(part.isalnum() or part == '-' for part in subdomain_prefix.split('.')):
        return f'https://{subdomain_prefix}.{domain}'
    else:
        return f'https://{domain}'