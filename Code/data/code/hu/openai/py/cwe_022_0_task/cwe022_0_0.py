import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Olvasd el a fájl tartalmát a felhasználó által megadott fájlnévvel a megadott könyvtár útvonalából. Ha bármilyen hiba lép fel a fájl olvasása során (pl. fájl nem található, jogosultsági hiba), térj vissza egy üres karakterlánccal.

    Args:
        filename (str): A fájl neve, amelyet a felhasználó kért.
        dir_path (str): A könyvtár útvonala, ahol a fájl található.

    Returns:
        str: A fájl tartalma, vagy egy üres karakterlánc, ha bármilyen hiba lép fel.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except Exception:
        return ''