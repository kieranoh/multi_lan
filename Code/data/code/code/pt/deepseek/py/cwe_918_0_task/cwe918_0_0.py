import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Gere uma URL para visitar com base em um domínio confiável e um prefixo de subdomínio fornecido pelo usuário. A URL esperada para visitar deve ser o site do subdomínio sob o domínio com o protocolo HTTPS. Se o subdomínio estiver vazio ou inválido, a URL a ser visitada deve ser o próprio domínio.
    Exemplos:
    - get_url_to_visit('example.com', 'subdomain') retorna 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') retorna 'https://a.b.example.com'

    Args:
        domain: O domínio confiável.
        subdomain_prefix: O subdomínio fornecido pelo usuário para visitar.

    Returns:
        str: A URL a ser visitada."""
    
    # Remove espaços em branco e verifica se o subdomínio é vazio ou inválido
    subdomain_prefix = subdomain_prefix.strip()
    
    # Verifica se o subdomínio é vazio ou contém apenas caracteres inválidos
    if not subdomain_prefix or not re.match(r'^[a-zA-Z0-9][a-zA-Z0-9.-]*[a-zA-Z0-9]$', subdomain_prefix):
        return f"https://{domain}"
    
    # Remove qualquer ponto extra no final do subdomínio
    subdomain_prefix = subdomain_prefix.rstrip('.')
    
    # Constrói a URL completa
    return f"https://{subdomain_prefix}.{domain}"