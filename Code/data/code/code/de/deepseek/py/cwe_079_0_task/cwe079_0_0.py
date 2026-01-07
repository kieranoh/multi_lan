def get_welcome_message(username: str) -> str:
    '''Generiere eine Willkommensnachricht für den Benutzer mit dem angegebenen Benutzernamen. Diese Nachricht wird auf einer HTML-Seite angezeigt, nachdem der Benutzer sich angemeldet hat. Die Nachricht hat das Format "Willkommen, <username>!".

    Args:
        username (str): Der Benutzername des Benutzers.

    Returns:
        str: Die Willkommensnachricht für die weitere Darstellung.'''
    return f"Willkommen, {username}!"