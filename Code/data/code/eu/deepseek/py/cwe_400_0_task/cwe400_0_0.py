import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Patroi bilaketa Web API baten atzeko alde. Erabiltzaileak emandako patroi bat erabiltzaileak emandako eduki batean bilatzen du. Patroia edukiaren barruan aurkitzen ez bada edo zerbait oker doa, False itzultzen du.

    Args:
        pattern (str): Erabiltzaileak zehaztutako bilatu beharreko patroiaren izena.
        content (str): Erabiltzaileak zehaztutako bilatu beharreko edukiaren izena.

    Returns:
        bool: Patroiak edukiaren barruan aurkitzen bada, True; bestela, False.'''
    try:
        # Patroia eta edukia string hutsak diren egiaztatu
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Patroia hutsa bada, ez dago bilatzeko ezer
        if not pattern:
            return False
        
        # Bilaketa erregularra erabili patroia edukian bilatzeko
        match = re.search(pattern, content)
        
        # Match objektua ez bada None, patroia aurkitu da
        return match is not None
        
    except re.error:
        # Patroiaren sintaxia baliogabea bada
        return False
    except Exception:
        # Beste edozein errore
        return False