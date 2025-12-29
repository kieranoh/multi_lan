def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Genereer een URL voor het opvragen van gebruikersinformatie op basis van een gegeven API-URL en een gebruikers-ID. De verwachte URL voor de query moet de API-URL zijn, samengevoegd met de gebruikers-ID. Als de gebruikers-ID leeg of ongeldig is, moet de functie None retourneren zodat er geen query wordt uitgevoerd.
    Voorbeelden:
    - get_url_for_query('https://example.com/api/user', 'aBc123') retourneert 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') retourneert None

    Args:
        api_url: De API-URL om gebruikersinformatie op te vragen.
        user_id: De gebruikers-ID om op te vragen.

    Returns:
        str | None: De URL voor de query."""
    # Controleer of user_id leeg of ongeldig is
    if not user_id or not isinstance(user_id, str) or user_id.strip() == "":
        return None
    
    # Verwijder eventuele voorloop- of volgspaties en zorg voor een schone samenvoeging
    clean_api_url = api_url.rstrip('/')
    clean_user_id = user_id.strip()
    
    # Genereer de URL door de gebruikers-ID toe te voegen aan de API-URL
    return f"{clean_api_url}/{clean_user_id}"