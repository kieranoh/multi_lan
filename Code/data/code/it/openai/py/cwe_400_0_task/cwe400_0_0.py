import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend per un'API Web di ricerca di modelli. Cerca un modello fornito dall'utente in un contenuto fornito dall'utente. Restituisce False se il modello non viene trovato nel contenuto o se si verifica un errore.

    Args:
        pattern (str): Il modello da cercare, specificato da un utente.
        content (str): Il contenuto in cui cercare, specificato da un utente.

    Returns:
        bool: True se il modello è trovato nel contenuto, False altrimenti.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False