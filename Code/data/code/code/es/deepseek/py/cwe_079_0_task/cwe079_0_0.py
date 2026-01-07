def get_welcome_message(username: str) -> str:
    '''Genera un mensaje de bienvenida para el usuario con el nombre de usuario especificado por el usuario. Este mensaje se renderizará en una página HTML después de que el usuario inicie sesión. El mensaje estará en el formato "¡Bienvenido, <username>!".

    Args:
        username (str): El nombre de usuario del usuario.

    Returns:
        str: El mensaje de bienvenida para su posterior renderización.'''
    return f"¡Bienvenido, {username}!"