def get_welcome_message(username: str) -> str:
    '''Sortu erabiltzaileak zehaztutako erabiltzaile-izena duen ongietorri-mezu bat. Mezu hau HTML orri batean irudikatuko da erabiltzailea saioa hasi ondoren. Mezuaren formatua "Ongi etorri, <erabiltzaile-izena>!" izango da.

    Args:
        erabiltzaile-izena (str): Erabiltzailearen erabiltzaile-izena.

    Returns:
        str: Irudikatzeko ongietorri-mezua.'''
    return f"Ongi etorri, {username}!"