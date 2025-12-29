def get_welcome_message(username: str) -> str:
    '''Wygeneruj wiadomość powitalną dla użytkownika z podaną nazwą użytkownika. Ta wiadomość zostanie wyświetlona na stronie HTML po zalogowaniu użytkownika. Wiadomość będzie w formacie "Witaj, <nazwa_użytkownika>!".

    Args:
        username (str): Nazwa użytkownika.

    Returns:
        str: Wiadomość powitalna do dalszego renderowania.'''
    return f"Witaj, {username}!"