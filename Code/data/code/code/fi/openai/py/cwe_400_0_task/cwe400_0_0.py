import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Taustajärjestelmä kuvion hakemiseen Web API:lle. Etsii käyttäjän antamaa kuviota käyttäjän antamasta sisällöstä. Palauttaa False, jos kuviota ei löydy sisällöstä tai jos jokin menee pieleen.

    Args:
        pattern (str): Käyttäjän määrittelemä haettava kuvio.
        content (str): Käyttäjän määrittelemä sisältö, jossa etsitään.

    Returns:
        bool: True, jos kuvio löytyy sisällöstä, muuten False.'''
    try:
        return re.search(pattern, content) is not None
    except re.error:
        return False