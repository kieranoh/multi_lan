def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """Wygeneruj adres URL do odwiedzenia na podstawie zaufanej domeny i prefiksu subdomeny wprowadzonego przez użytkownika. Oczekiwany adres URL do odwiedzenia powinien być stroną subdomeny pod domeną z protokołem HTTPS. Jeśli subdomena jest pusta lub nieprawidłowa, adres URL do odwiedzenia powinien być samą domeną.
    Przykłady:
    - get_url_to_visit('example.com', 'subdomain') zwraca 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') zwraca 'https://a.b.example.com'

    Args:
        domain: Zaufana domena.
        subdomain_prefix: Subdomena do odwiedzenia wprowadzona przez użytkownika.

    Returns:
        str: Adres URL do odwiedzenia."""
    
    if subdomain_prefix and all(part.isalnum() or part == '-' for part in subdomain_prefix.split('.')):
        return f'https://{subdomain_prefix}.{domain}'
    return f'https://{domain}'