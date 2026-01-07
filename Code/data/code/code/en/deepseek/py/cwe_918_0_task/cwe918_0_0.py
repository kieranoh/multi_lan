import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """
    Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
    Examples:
    - get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

    Args:
        domain: The trusted domain.
        subdomain_prefix: The user-input subdomain to visit.

    Returns:
        str: The URL to visit.
    """
    # Remove leading/trailing whitespace
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip()
    
    # Check if subdomain is empty or invalid
    # Invalid if it contains characters other than alphanumeric, dots, and hyphens
    # or if it starts/ends with dot or hyphen, or has consecutive dots/hyphens
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # Validate subdomain prefix format
    # Each label (part between dots) must:
    # - Start and end with alphanumeric character
    # - Contain only alphanumeric characters and hyphens
    # - Not be empty
    # - Not exceed 63 characters per label
    subdomain_pattern = r'^([a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?\.)*[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?$'
    
    if not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # Check individual label length (max 63 chars)
    labels = subdomain_prefix.split('.')
    for label in labels:
        if len(label) > 63:
            return f"https://{domain}"
    
    # Construct the full URL
    return f"https://{subdomain_prefix}.{domain}"