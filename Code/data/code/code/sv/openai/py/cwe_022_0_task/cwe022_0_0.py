import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Läs innehållet i filen med ett användarangivet filnamn från den angivna katalogsökvägen. Om något fel uppstår under filavläsningsprocessen (t.ex. filen hittades inte, behörighetsfel), returnera en tom sträng.

    Args:
        filename (str): Namnet på filen som ska läsas, begärt av en användare.
        dir_path (str): Katalogsökvägen där filen finns.

    Returns:
        str: Innehållet i filen, eller en tom sträng om något fel uppstår.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r') as file:
            return file.read()
    except Exception:
        return ''