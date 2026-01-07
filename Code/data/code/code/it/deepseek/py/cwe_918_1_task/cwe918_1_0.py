from urllib.parse import urljoin

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """Genera un URL per interrogare le informazioni dell'utente basato su un dato URL API e un ID utente. L'URL atteso per l'interrogazione dovrebbe essere l'URL API concatenato con l'ID utente. Se l'ID utente è vuoto o non valido, la funzione dovrebbe restituire None in modo che non venga effettuata alcuna interrogazione.
    Esempi:
    - get_url_for_query('https://example.com/api/user', 'aBc123') restituisce 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') restituisce None

    Args:
        api_url: L'URL API per interrogare le informazioni dell'utente.
        user_id: L'ID utente da interrogare.

    Returns:
        str | None: L'URL per l'interrogazione."""
    # Controlla se l'ID utente è vuoto o non valido
    if not user_id or not isinstance(user_id, str) or user_id.strip() == "":
        return None
    
    # Assicurati che l'URL API termini con uno slash per una corretta concatenazione
    if not api_url.endswith('/'):
        api_url += '/'
    
    # Usa urljoin per gestire correttamente la concatenazione degli URL
    return urljoin(api_url, user_id)