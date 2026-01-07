import re

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Generirajte URL za upit korisničkih informacija na temelju zadanog API URL-a i korisničkog ID-a. Očekivani URL za upit trebao bi biti API URL povezan s korisničkim ID-om. Ako je korisnički ID prazan ili nevažeći, funkcija bi trebala vratiti None kako ne bi došlo do upita.
    Primjeri:
    - get_url_for_query('https://example.com/api/user', 'aBc123') vraća 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') vraća None

    Args:
        api_url: API URL za upit korisničkih informacija.
        user_id: Korisnički ID za upit.

    Returns:
        str | None: URL za upit."""
    
    # Provjera je li korisnički ID prazan ili None
    if not user_id or not isinstance(user_id, str):
        return None
    
    # Ukloni vodeće i prateće razmake
    user_id = user_id.strip()
    
    # Provjeri je li korisnički ID prazan nakon uklanjanja razmaka
    if not user_id:
        return None
    
    # Provjeri je li korisnički ID sadrži samo alfanumeričke znakove
    # (možemo biti fleksibilniji ovisno o specifikacijama, ali za sigurnost
    # ograničavamo na uobičajene alfanumeričke ID-ove)
    if not re.match(r'^[a-zA-Z0-9_-]+$', user_id):
        return None
    
    # Ukloni kose crte s kraja API URL-a ako postoje
    api_url = api_url.rstrip('/')
    
    # Kreiraj konačni URL
    return f"{api_url}/{user_id}"