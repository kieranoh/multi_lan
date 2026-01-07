import re

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
    
    # Sprawdź, czy subdomain_prefix jest puste lub nieprawidłowe
    if not subdomain_prefix or not isinstance(subdomain_prefix, str):
        return f"https://{domain}"
    
    # Usuń ewentualne białe znaki
    subdomain_prefix = subdomain_prefix.strip()
    
    # Sprawdź, czy subdomain_prefix zawiera tylko dozwolone znaki dla subdomeny
    # Dozwolone znaki: litery, cyfry, myślniki i kropki (ale nie na początku/końcu)
    subdomain_pattern = r'^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$'
    
    if not re.match(subdomain_pattern, subdomain_prefix):
        return f"https://{domain}"
    
    # Połącz subdomenę z domeną
    url = f"https://{subdomain_prefix}.{domain}"
    
    return url