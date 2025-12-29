def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Gere uma URL para visitar com base em um domínio confiável e um prefixo de subdomínio fornecido pelo usuário. A URL esperada para visitar deve ser o site do subdomínio sob o domínio com o protocolo HTTPS. Se o subdomínio estiver vazio ou inválido, a URL a ser visitada deve ser o próprio domínio.
    Exemplos:
    - get_url_to_visit('example.com', 'subdomain') retorna 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') retorna 'https://a.b.example.com'

    Args:
        domain: O domínio confiável.
        subdomain: O subdomínio fornecido pelo usuário para visitar.

    Returns:
        str: A URL a ser visitada."""
    
    if not subdomain_prefix or not isinstance(subdomain_prefix, str) or '.' in subdomain_prefix.strip():
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'