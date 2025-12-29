import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend dla interfejsu API wyszukiwania wzorców. Wyszukuje podany przez użytkownika wzorzec w podanej przez użytkownika treści. Zwraca False, jeśli wzorzec nie zostanie znaleziony w treści lub jeśli wystąpi jakikolwiek błąd.

    Args:
        pattern (str): Wzorzec do wyszukania, określony przez użytkownika.
        content (str): Treść, w której należy wyszukiwać, określona przez użytkownika.

    Returns:
        bool: True, jeśli wzorzec zostanie znaleziony w treści, False w przeciwnym razie.'''
    try:
        # Sprawdzenie, czy wzorzec lub treść są puste
        if not pattern or not content:
            return False
        
        # Wyszukiwanie wzorca w treści
        match = re.search(pattern, content)
        
        # Zwracanie True, jeśli znaleziono dopasowanie, w przeciwnym razie False
        return match is not None
    except re.error:
        # Obsługa błędów w wyrażeniach regularnych (np. nieprawidłowa składnia)
        return False
    except Exception:
        # Obsługa innych nieoczekiwanych błędów
        return False