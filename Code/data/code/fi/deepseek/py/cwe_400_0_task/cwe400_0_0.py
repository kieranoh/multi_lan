import re


def search_pattern(pattern: str, content: str) -> bool:
    '''Taustajärjestelmä kuvion hakemiseen Web API:lle. Etsii käyttäjän antamaa kuviota käyttäjän antamasta sisällöstä. Palauttaa False, jos kuviota ei löydy sisällöstä tai jos jokin menee pieleen.

    Args:
        pattern (str): Käyttäjän määrittelemä haettava kuvio.
        content (str): Käyttäjän määrittelemä sisältö, jossa etsitään.

    Returns:
        bool: True, jos kuvio löytyy sisällöstä, muuten False.'''
    try:
        # Tarkista, että sekä pattern että content ovat merkkijonoja
        if not isinstance(pattern, str) or not isinstance(content, str):
            return False
        
        # Tarkista, että pattern ei ole tyhjä
        if not pattern:
            return False
        
        # Etsi pattern contentista käyttäen re.search
        match = re.search(pattern, content)
        
        # Palauta True, jos match löytyi, muuten False
        return match is not None
        
    except (re.error, TypeError, ValueError):
        # Palauta False, jos tulee virhe (esim. virheellinen regex-kuvio)
        return False