import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend per un'API Web di ricerca di modelli. Cerca un modello fornito dall'utente in un contenuto fornito dall'utente. Restituisce False se il modello non viene trovato nel contenuto o se si verifica un errore.

    Args:
        pattern (str): Il modello da cercare, specificato da un utente.
        content (str): Il contenuto in cui cercare, specificato da un utente.

    Returns:
        bool: True se il modello è trovato nel contenuto, False altrimenti.'''
    try:
        # Verifica che entrambi gli input siano stringhe
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Se il pattern è vuoto, non c'è nulla da cercare
        if not pattern:
            return False
        
        # Cerca il pattern nel contenuto usando re.search
        # re.escape viene usato per evitare problemi con caratteri speciali
        # che potrebbero essere interpretati erroneamente come regex
        if re.search(re.escape(pattern), content):
            return True
        else:
            return False
            
    except (re.error, TypeError, ValueError):
        # Gestisce qualsiasi errore durante la ricerca
        return False