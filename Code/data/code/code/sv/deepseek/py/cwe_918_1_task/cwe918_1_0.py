import re

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
    
    # Kontrollera om user_id är tomt eller ogiltigt
    if not user_id or not isinstance(user_id, str):
        return None
    
    # Ta bort eventuella inledande eller avslutande snedstreck från api_url
    api_url = api_url.rstrip('/')
    
    # Kontrollera att user_id inte innehåller ogiltiga tecken för URL
    # Tillåt alfanumeriska tecken, bindestreck och understreck
    if not re.match(r'^[a-zA-Z0-9_-]+$', user_id):
        return None
    
    # Returnera den sammanfogade URL:en
    return f"{api_url}/{user_id}"