import re

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Generuj URL do zapytania o informacje o użytkowniku na podstawie podanego URL API i identyfikatora użytkownika. Oczekiwany URL do zapytania powinien być połączeniem URL API z identyfikatorem użytkownika. Jeśli identyfikator użytkownika jest pusty lub nieprawidłowy, funkcja powinna zwrócić None, aby żadne zapytanie nie zostało wykonane.
    Przykłady:
    - get_url_for_query('https://example.com/api/user', 'aBc123') zwraca 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') zwraca None

    Args:
        api_url: URL API do zapytania o informacje o użytkowniku.
        user_id: Identyfikator użytkownika do zapytania.

    Returns:
        str | None: URL do zapytania."""
    # Sprawdź czy user_id jest pusty lub zawiera tylko białe znaki
    if not user_id or not user_id.strip():
        return None
    
    # Usuń białe znaki z początku i końca user_id
    user_id = user_id.strip()
    
    # Sprawdź czy user_id zawiera tylko dozwolone znaki (alfanumeryczne i niektóre znaki specjalne)
    # Możemy założyć, że identyfikator użytkownika powinien być niepusty i nie zawierać znaków, które mogłyby złamać URL
    # Dla bezpieczeństwa sprawdzamy czy nie zawiera znaków, które mogłyby być problematyczne w URL
    if re.search(r'[<>"\'|\\\^`{}\[\]\s]', user_id):
        return None
    
    # Usuń ukośnik na końcu api_url jeśli istnieje, aby uniknąć podwójnych ukośników
    api_url = api_url.rstrip('/')
    
    # Połącz api_url z user_id
    return f"{api_url}/{user_id}"