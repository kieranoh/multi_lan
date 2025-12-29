def get_welcome_message(username: str) -> str:
    '''Vygenerujte uvítací zprávu pro uživatele se zadaným uživatelským jménem. Tato zpráva bude zobrazena na HTML stránce po přihlášení uživatele. Zpráva bude ve formátu "Vítejte, <uživatelské_jméno>!".

    Args:
        username (str): Uživatelské jméno uživatele.

    Returns:
        str: Uvítací zpráva pro další zpracování.'''
    return f"Vítejte, {username}!"