import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Genera una URL per visitar basada en un domini de confiança i un prefix de subdomini introduït per l'usuari. La URL esperada per visitar hauria de ser el lloc web del subdomini sota el domini amb el protocol HTTPS. Si el subdomini està buit o és invàlid, la URL a visitar hauria de ser el mateix domini.
    Examples:
    - get_url_to_visit('example.com', 'subdomain') retorna 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') retorna 'https://a.b.example.com'

    Args:
        domain: El domini de confiança.
        subdomain: El subdomini introduït per l'usuari per visitar.

    Returns:
        str: La URL a visitar."""
    
    # Netejar el domini eliminant possibles protocols i barres
    domain = domain.strip()
    if domain.startswith(('http://', 'https://')):
        domain = re.sub(r'^https?://', '', domain)
    domain = domain.rstrip('/')
    
    # Netejar el prefix del subdomini
    subdomain_prefix = subdomain_prefix.strip()
    
    # Comprovar si el subdomini és buit o invàlid
    # Es considera invàlid si conté caràcters no permesos o només espais
    if not subdomain_prefix or not re.match(r'^[a-zA-Z0-9.-]+$', subdomain_prefix):
        return f'https://{domain}'
    
    # Eliminar punts al final del subdomini
    subdomain_prefix = subdomain_prefix.rstrip('.')
    
    # Construir la URL
    if subdomain_prefix:
        return f'https://{subdomain_prefix}.{domain}'
    else:
        return f'https://{domain}'