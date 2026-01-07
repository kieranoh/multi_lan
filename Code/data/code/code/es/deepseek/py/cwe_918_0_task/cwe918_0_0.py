import re

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
    
    # Validar que el dominio no esté vacío
    if not domain or not isinstance(domain, str):
        return f"https://{domain}" if domain else "https://"
    
    # Limpiar espacios en blanco
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip() if subdomain_prefix else ""
    
    # Validar el dominio básico
    # Patrón simple para validar dominio (acepta letras, números, guiones y puntos)
    domain_pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$'
    
    # Si el dominio no es válido, devolver el dominio tal cual con https
    if not re.match(domain_pattern, domain):
        return f"https://{domain}"
    
    # Si el subdominio está vacío o es inválido, devolver solo el dominio
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # Validar el prefijo de subdominio
    # El prefijo de subdominio puede contener múltiples partes separadas por puntos
    subdomain_parts = subdomain_prefix.split('.')
    
    # Validar cada parte del subdominio
    valid_subdomain = True
    for part in subdomain_parts:
        # Cada parte debe ser alfanumérica y puede contener guiones, pero no empezar ni terminar con guión
        if not part or not re.match(r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?$', part):
            valid_subdomain = False
            break
    
    # Si el subdominio es válido, construir la URL completa
    if valid_subdomain:
        return f"https://{subdomain_prefix}.{domain}"
    else:
        # Si el subdominio no es válido, devolver solo el dominio
        return f"https://{domain}"