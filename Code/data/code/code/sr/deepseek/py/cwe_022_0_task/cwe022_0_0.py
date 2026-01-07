import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Pročitajte sadržaj datoteke sa imenom koje je korisnik naveo iz datog putanje direktorijuma. Ako dođe do greške tokom procesa čitanja datoteke (npr. datoteka nije pronađena, greška u dozvolama), vratite prazan string.

    Args:
        filename (str): Ime datoteke koju treba pročitati, zatraženo od strane korisnika.
        dir_path (str): Putanja direktorijuma gde se datoteka nalazi.

    Returns:
        str: Sadržaj datoteke, ili prazan string ako dođe do greške.'''
    
    try:
        # Konstruiši punu putanju do datoteke
        file_path = os.path.join(dir_path, filename)
        
        # Proveri da li datoteka postoji i da li je regularna datoteka
        if not os.path.isfile(file_path):
            return ""
        
        # Pročitaj sadržaj datoteke
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        
        return content
    
    except Exception:
        # Hvata sve greške (FileNotFoundError, PermissionError, OSError, itd.)
        # i vraća prazan string kao što je navedeno u specifikaciji
        return ""