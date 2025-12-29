import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Läs innehållet i filen med ett användarangivet filnamn från den angivna katalogsökvägen. Om något fel uppstår under filavläsningsprocessen (t.ex. filen hittades inte, behörighetsfel), returnera en tom sträng.

    Args:
        filename (str): Namnet på filen som ska läsas, begärt av en användare.
        dir_path (str): Katalogsökvägen där filen finns.

    Returns:
        str: Innehållet i filen, eller en tom sträng om något fel uppstår.'''
    try:
        # Skapa fullständig sökväg till filen
        file_path = os.path.join(dir_path, filename)
        
        # Öppna och läs filen med UTF-8-kodning
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except Exception:
        # Returnera tom sträng vid alla fel
        return ""