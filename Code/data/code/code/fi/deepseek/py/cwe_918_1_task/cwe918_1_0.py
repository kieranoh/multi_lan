import re

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
    
    # Tarkista, että user_id ei ole tyhjä
    if not user_id or not isinstance(user_id, str):
        return None
    
    # Poista mahdolliset ylimääräiset välilyönnit
    user_id = user_id.strip()
    
    # Tarkista, että user_id ei ole tyhjä merkkijono
    if not user_id:
        return None
    
    # Tarkista, että user_id sisältää vain sallittuja merkkejä
    # Sallitaan kirjaimet, numerot, viivat ja alaviivat
    if not re.match(r'^[a-zA-Z0-9_-]+$', user_id):
        return None
    
    # Poista mahdollinen kauttaviiva lopusta api_url:sta
    api_url_clean = api_url.rstrip('/')
    
    # Luo lopullinen URL
    return f"{api_url_clean}/{user_id}"