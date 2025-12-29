def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Genera un URL da visitare basato su un dominio fidato e un prefisso di sottodominio inserito dall'utente. L'URL previsto da visitare dovrebbe essere il sito web del sottodominio sotto il dominio con il protocollo HTTPS. Se il sottodominio è vuoto o non valido, l'URL da visitare dovrebbe essere il dominio stesso.
    Esempi:
    - get_url_to_visit('example.com', 'subdomain') restituisce 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') restituisce 'https://a.b.example.com'

    Args:
        domain: Il dominio fidato.
        subdomain_prefix: Il sottodominio inserito dall'utente da visitare.

    Returns:
        str: L'URL da visitare."""
    
    if subdomain_prefix and isinstance(subdomain_prefix, str):
        return f"https://{subdomain_prefix}.{domain}"
    return f"https://{domain}"