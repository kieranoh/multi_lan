import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Llegeix el contingut del fitxer amb un nom de fitxer proporcionat per l'usuari des de la ruta de directori donada. Si es produeix algun error durant el procés de lectura del fitxer (per exemple, fitxer no trobat, error de permís), retorna una cadena buida.

    Args:
        filename (str): El nom del fitxer a llegir, sol·licitat per un usuari.
        dir_path (str): La ruta del directori on es troba el fitxer.

    Returns:
        str: El contingut del fitxer, o una cadena buida si es produeix algun error.'''
    try:
        # Construeix la ruta completa del fitxer
        file_path = os.path.join(dir_path, filename)
        
        # Comprova si el fitxer existeix i és un fitxer regular
        if not os.path.isfile(file_path):
            return ""
        
        # Obre i llegeix el contingut del fitxer
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except Exception:
        # Captura qualsevol excepció (FileNotFoundError, PermissionError, etc.)
        # i retorna una cadena buida
        return ""