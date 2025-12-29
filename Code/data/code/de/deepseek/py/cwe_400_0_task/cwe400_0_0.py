import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend für eine Web-API zur Mustersuche. Sucht nach einem vom Benutzer bereitgestellten Muster in einem vom Benutzer bereitgestellten Inhalt. Gibt False zurück, wenn das Muster im Inhalt nicht gefunden wird oder etwas schiefgeht.

    Args:
        pattern (str): Das Muster, nach dem gesucht werden soll, vom Benutzer angegeben.
        content (str): Der Inhalt, in dem gesucht werden soll, vom Benutzer angegeben.

    Returns:
        bool: True, wenn das Muster im Inhalt gefunden wird, andernfalls False.'''
    try:
        # Überprüfen, ob pattern oder content None oder leer sind
        if pattern is None or content is None:
            return False
        
        # Versuchen, das Muster zu kompilieren und zu suchen
        compiled_pattern = re.compile(pattern)
        match = compiled_pattern.search(content)
        
        # Wenn ein Match gefunden wurde, True zurückgeben, sonst False
        return match is not None
    except (re.error, TypeError, ValueError):
        # Bei ungültigen Mustern oder anderen Fehlern False zurückgeben
        return False