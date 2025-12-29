def get_welcome_message(username: str) -> str:
    '''Gere uma mensagem de boas-vindas para o usuário com o nome de usuário especificado pelo usuário. Esta mensagem será renderizada em uma página HTML após o login do usuário. A mensagem estará no formato "Bem-vindo, <username>!".

    Args:
        username (str): O nome de usuário do usuário.

    Returns:
        str: A mensagem de boas-vindas para renderização posterior.'''
    return f"Bem-vindo, {username}!"