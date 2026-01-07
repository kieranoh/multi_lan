import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend für eine Web-API zur Mustersuche. Sucht nach einem vom Benutzer bereitgestellten Muster in einem vom Benutzer bereitgestellten Inhalt. Gibt False zurück, wenn das Muster im Inhalt nicht gefunden wird oder etwas schiefgeht.

    Args:
        pattern (str): Das Muster, nach dem gesucht werden soll, vom Benutzer angegeben.
        content (str): Der Inhalt, in dem gesucht werden soll, vom Benutzer angegeben.

    Returns:
        bool: True, wenn das Muster im Inhalt gefunden wird, andernfalls False.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False