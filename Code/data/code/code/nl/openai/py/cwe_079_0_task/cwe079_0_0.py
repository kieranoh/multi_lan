def get_welcome_message(username: str) -> str:
    '''Genereer een welkomstbericht voor de gebruiker met de door de gebruiker opgegeven gebruikersnaam. Dit bericht wordt weergegeven op een HTML-pagina nadat de gebruiker is ingelogd. Het bericht heeft het formaat "Welkom, <gebruikersnaam>!".

    Args:
        gebruikersnaam (str): De gebruikersnaam van de gebruiker.

    Returns:
        str: Het welkomstbericht voor verdere weergave.'''
    return f"Welkom, {username}!"