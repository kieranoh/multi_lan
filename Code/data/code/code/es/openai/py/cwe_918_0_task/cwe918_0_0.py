def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Genera una URL para visitar basada en un dominio de confianza y un prefijo de subdominio ingresado por el usuario. La URL esperada para visitar debe ser el sitio web del subdominio bajo el dominio con el protocolo HTTPS. Si el subdominio está vacío o es inválido, la URL a visitar debe ser el dominio en sí.
    Ejemplos:
    - get_url_to_visit('example.com', 'subdomain') devuelve 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') devuelve 'https://a.b.example.com'

    Args:
        domain: El dominio de confianza.
        subdomain_prefix: El subdominio ingresado por el usuario para visitar.

    Returns:
        str: La URL a visitar."""
    
    if not subdomain_prefix or any(part == '' for part in subdomain_prefix.split('.')):
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'