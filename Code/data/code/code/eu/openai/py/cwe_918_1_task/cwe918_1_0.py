def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Erabiltzailearen informazioa eskuratzeko URL bat sortu emandako API URL eta erabiltzaile ID baten arabera. Espektatutako URL-a API URL-a erabiltzaile IDarekin batzen dena izan behar da. Erabiltzaile ID-a hutsik edo baliogabea bada, funtzioak None itzuli behar du, beraz, ez da inolako galderarik egingo.
    Adibideak:
    - get_url_for_query('https://example.com/api/user', 'aBc123') itzultzen du 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') itzultzen du None

    Args:
        api_url: Erabiltzailearen informazioa eskuratzeko API URL-a.
        user_id: Eskaeratzeko erabiltzaile ID-a.

    Returns:
        str | None: Eskaerako URL-a."""
    
    if not user_id:
        return None
    return f"{api_url}/{user_id}"