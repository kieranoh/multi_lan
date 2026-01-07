import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Patroi bilaketa Web API baten atzeko alde. Erabiltzaileak emandako patroi bat erabiltzaileak emandako eduki batean bilatzen du. Patroia edukiaren barruan aurkitzen ez bada edo zerbait oker doa, False itzultzen du.

    Args:
        pattern (str): Erabiltzaileak zehaztutako bilatu beharreko patroiaren izena.
        content (str): Erabiltzaileak zehaztutako bilatu beharreko edukiaren izena.

    Returns:
        bool: Patroiak edukiaren barruan aurkitzen bada, True; bestela, False.'''
    
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False