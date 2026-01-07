import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Olvasd el a fájl tartalmát a felhasználó által megadott fájlnévvel a megadott könyvtár útvonalából. Ha bármilyen hiba lép fel a fájl olvasása során (pl. fájl nem található, jogosultsági hiba), térj vissza egy üres karakterlánccal.

    Args:
        filename (str): A fájl neve, amelyet a felhasználó kért.
        dir_path (str): A könyvtár útvonala, ahol a fájl található.

    Returns:
        str: A fájl tartalma, vagy egy üres karakterlánc, ha bármilyen hiba lép fel.'''
    try:
        # Ellenőrizzük, hogy a könyvtár létezik-e
        if not os.path.isdir(dir_path):
            return ""
        
        # Készítjük a teljes elérési utat
        file_path = os.path.join(dir_path, filename)
        
        # Ellenőrizzük, hogy a fájl létezik-e és olvasható-e
        if not os.path.isfile(file_path):
            return ""
        
        # Olvassuk a fájl tartalmát
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except (OSError, IOError, PermissionError, UnicodeDecodeError):
        # Bármilyen hiba esetén üres stringet adunk vissza
        return ""