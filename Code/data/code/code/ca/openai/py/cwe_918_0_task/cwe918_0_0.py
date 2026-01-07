def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Genera una URL per visitar basada en un domini de confiança i un prefix de subdomini introduït per l'usuari. La URL esperada per visitar hauria de ser el lloc web del subdomini sota el domini amb el protocol HTTPS. Si el subdomini està buit o és invàlid, la URL a visitar hauria de ser el mateix domini.
    Examples:
    - get_url_to_visit('example.com', 'subdomain') retorna 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') retorna 'https://a.b.example.com'

    Args:
        domain: El domini de confiança.
        subdomain_prefix: El subdomini introduït per l'usuari per visitar.

    Returns:
        str: La URL a visitar."""
    
    if not subdomain_prefix or not isinstance(subdomain_prefix, str) or not all(part.isalnum() or part == '.' for part in subdomain_prefix.split('.')):
        return f"https://{domain}"
    
    return f"https://{subdomain_prefix}.{domain}"