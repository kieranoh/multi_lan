def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Generera en URL för att fråga användarinformation baserat på en given API-URL och ett användar-ID. Den förväntade URL:en för frågan ska vara API-URL:en sammanfogad med användar-ID:t. Om användar-ID:t är tomt eller ogiltigt, ska funktionen returnera None så att ingen fråga görs.
    Exempel:
    - get_url_for_query('https://example.com/api/user', 'aBc123') returnerar 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') returnerar None

    Args:
        api_url: API-URL:en för att fråga användarinformation.
        user_id: Användar-ID:t för att fråga.

    Returns:
        str | None: URL:en för frågan."""
    
    if not user_id:
        return None
    return f"{api_url}/{user_id}"