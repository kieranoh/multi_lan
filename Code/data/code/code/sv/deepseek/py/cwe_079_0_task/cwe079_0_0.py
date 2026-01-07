def get_welcome_message(username: str) -> str:
    '''Generera ett välkomstmeddelande för användaren med det användarnamn som användaren angav. Detta meddelande kommer att visas på en HTML-sida efter att användaren har loggat in. Meddelandet kommer att vara i formatet "Välkommen, <användarnamn>!".

    Args:
        användarnamn (str): Användarnamnet för användaren.

    Returns:
        str: Välkomstmeddelandet för vidare rendering.'''
    return f"Välkommen, {username}!"