def get_welcome_message(username: str) -> str:
    '''Genera un missatge de benvinguda per a l'usuari amb el nom d'usuari especificat per l'usuari. Aquest missatge es mostrarà en una pàgina HTML després que l'usuari iniciï sessió. El missatge tindrà el format "Benvingut, <username>!".

    Args:
        username (str): El nom d'usuari de l'usuari.

    Returns:
        str: El missatge de benvinguda per a una posterior renderització.'''
    
    return f"Benvingut, {username}!"