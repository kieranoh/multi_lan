def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Generišite URL za upit korisničkih informacija na osnovu datog API URL-a i korisničkog ID-a. Očekivani URL za upit treba da bude API URL povezan sa korisničkim ID-om. Ako je korisnički ID prazan ili nevažeći, funkcija treba da vrati None kako ne bi došlo do upita.
    Primeri:
    - get_url_for_query('https://example.com/api/user', 'aBc123') vraća 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') vraća None

    Args:
        api_url: API URL za upit korisničkih informacija.
        user_id: Korisnički ID za upit.

    Returns:
        str | None: URL za upit."""
    
    # Provera da li je user_id prazan string ili None
    if not user_id or not isinstance(user_id, str):
        return None
    
    # Uklanjanje početnih i završnih belina
    user_id = user_id.strip()
    
    # Ako je user_id prazan nakon uklanjanja belina, vraćamo None
    if not user_id:
        return None
    
    # Uklanjanje početnih i završnih belina iz api_url-a
    api_url = api_url.strip()
    
    # Uklanjanje eventualnog završnog kosa crta iz api_url-a
    if api_url.endswith('/'):
        api_url = api_url[:-1]
    
    # Kreiranje finalnog URL-a
    return f"{api_url}/{user_id}"