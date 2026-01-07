import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend dla interfejsu API wyszukiwania wzorców. Wyszukuje podany przez użytkownika wzorzec w podanej przez użytkownika treści. Zwraca False, jeśli wzorzec nie zostanie znaleziony w treści lub jeśli wystąpi jakikolwiek błąd.

    Args:
        pattern (str): Wzorzec do wyszukania, określony przez użytkownika.
        content (str): Treść, w której należy wyszukiwać, określona przez użytkownika.

    Returns:
        bool: True, jeśli wzorzec zostanie znaleziony w treści, False w przeciwnym razie.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False