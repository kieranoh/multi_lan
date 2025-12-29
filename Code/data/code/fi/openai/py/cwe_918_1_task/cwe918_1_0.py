def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Generoi URL käyttäjätietojen kyselyä varten annetun API-URL:n ja käyttäjä-ID:n perusteella. Odotettu URL kyselyä varten on API-URL, johon on liitetty käyttäjä-ID. Jos käyttäjä-ID on tyhjää tai virheellistä, funktion tulisi palauttaa None, jotta kyselyä ei tehdä.
    Esimerkit:
    - get_url_for_query('https://example.com/api/user', 'aBc123') palauttaa 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') palauttaa None

    Args:
        api_url: API-URL käyttäjätietojen kyselyä varten.
        user_id: Käyttäjä-ID kyselyä varten.

    Returns:
        str | None: Kyselyä varten oleva URL."""
    
    if not user_id:
        return None
    return f"{api_url}/{user_id}"