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
    
    if not user_id:
        return None
    
    return f"{api_url}/{user_id}"