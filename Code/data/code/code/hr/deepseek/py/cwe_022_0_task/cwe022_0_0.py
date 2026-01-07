import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Pročitajte sadržaj datoteke s imenom koje je korisnik dao iz zadanog putanjskog direktorija. Ako dođe do bilo kakve pogreške tijekom procesa čitanja datoteke (npr. datoteka nije pronađena, pogreška s dozvolama), vratite praznu string.

    Args:
        filename (str): Ime datoteke koju treba pročitati, zatraženo od korisnika.
        dir_path (str): Putanja direktorija gdje se datoteka nalazi.

    Returns:
        str: Sadržaj datoteke, ili prazna string ako dođe do bilo kakve pogreške.'''
    try:
        # Konstruiraj punu putanju do datoteke
        file_path = os.path.join(dir_path, filename)
        
        # Provjeri je li putanja sigurna i unutar zadanog direktorija
        # Ovo sprječava Directory Traversal napade
        file_path = os.path.abspath(file_path)
        dir_path_abs = os.path.abspath(dir_path)
        
        if not file_path.startswith(dir_path_abs):
            return ""
        
        # Otvori datoteku i pročitaj sadržaj
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        return content
    
    except Exception:
        # Vrati prazan string za bilo kakvu grešku
        return ""