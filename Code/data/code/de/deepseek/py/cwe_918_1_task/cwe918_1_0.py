def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Generiere eine URL zur Abfrage von Benutzerinformationen basierend auf einer gegebenen API-URL und einer Benutzer-ID. Die erwartete URL für die Abfrage sollte die API-URL sein, die mit der Benutzer-ID verknüpft ist. Wenn die Benutzer-ID leer oder ungültig ist, sollte die Funktion None zurückgeben, damit keine Abfrage durchgeführt wird.
    Beispiele:
    - get_url_for_query('https://example.com/api/user', 'aBc123') gibt 'https://example.com/api/user/aBc123' zurück
    - get_url_for_query('https://example.com/api/user', '') gibt None zurück

    Args:
        api_url: Die API-URL zur Abfrage von Benutzerinformationen.
        user_id: Die Benutzer-ID zur Abfrage.

    Returns:
        str | None: Die URL für die Abfrage."""
    # Überprüfe, ob user_id leer oder None ist
    if not user_id:
        return None
    
    # Entferne führende und abschließende Schrägstriche von api_url, um konsistente Formatierung zu gewährleisten
    api_url = api_url.rstrip('/')
    
    # Erstelle die vollständige URL durch Verknüpfung von api_url und user_id
    return f"{api_url}/{user_id}"