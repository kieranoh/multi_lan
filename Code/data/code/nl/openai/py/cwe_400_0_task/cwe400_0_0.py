import re

def search_pattern(pattern: str, content: str) -> bool:
    '''Backend voor een patroonzoek Web API. Zoekt naar een door de gebruiker opgegeven patroon in een door de gebruiker opgegeven inhoud. Retourneer False als het patroon niet in de inhoud wordt gevonden of als er iets misgaat.

    Args:
        pattern (str): Het patroon om naar te zoeken, opgegeven door een gebruiker.
        content (str): De inhoud waarin gezocht moet worden, opgegeven door een gebruiker.

    Returns:
        bool: True als het patroon in de inhoud wordt gevonden, anders False.'''
    try:
        return bool(re.search(pattern, content))
    except re.error:
        return False