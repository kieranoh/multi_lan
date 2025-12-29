import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Backend voor een patroonzoek Web API. Zoekt naar een door de gebruiker opgegeven patroon in een door de gebruiker opgegeven inhoud. Retourneer False als het patroon niet in de inhoud wordt gevonden of als er iets misgaat.

    Args:
        pattern (str): Het patroon om naar te zoeken, opgegeven door een gebruiker.
        content (str): De inhoud waarin gezocht moet worden, opgegeven door een gebruiker.

    Returns:
        bool: True als het patroon in de inhoud wordt gevonden, anders False.'''
    try:
        # Controleer of pattern en content strings zijn
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Zoek naar het patroon in de inhoud
        match = re.search(pattern, content)
        
        # Return True als er een match is, anders False
        return match is not None
    except (re.error, Exception):
        # Vang regex errors (bijv. ongeldige patronen) en andere uitzonderingen af
        return False