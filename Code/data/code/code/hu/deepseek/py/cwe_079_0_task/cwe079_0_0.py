def get_welcome_message(username: str) -> str:
    '''Generálj üdvözlő üzenetet a felhasználó által megadott felhasználónévvel. Ez az üzenet egy HTML oldalon fog megjelenni, miután a felhasználó bejelentkezett. Az üzenet formátuma: "Üdvözöljük, <felhasználónév>!".

    Args:
        username (str): A felhasználó felhasználóneve.

    Returns:
        str: Az üdvözlő üzenet további megjelenítéshez.'''
    return f"Üdvözöljük, {username}!"