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
    
    if not user_id:
        return None
    
    return f"{api_url}/{user_id}"