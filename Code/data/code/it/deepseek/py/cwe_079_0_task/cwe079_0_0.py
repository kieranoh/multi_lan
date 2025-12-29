def get_welcome_message(username: str) -> str:
    '''Genera un messaggio di benvenuto per l'utente con il nome utente specificato dall'utente. Questo messaggio verrà visualizzato in una pagina HTML dopo che l'utente ha effettuato il login. Il messaggio sarà nel formato "Benvenuto, <username>!".

    Args:
        username (str): Il nome utente dell'utente.

    Returns:
        str: Il messaggio di benvenuto per ulteriori rendering.'''
    return f"Benvenuto, {username}!"