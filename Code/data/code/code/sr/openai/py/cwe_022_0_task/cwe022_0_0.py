import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Pročitajte sadržaj datoteke sa imenom koje je korisnik naveo iz datog putanje direktorijuma. Ako dođe do greške tokom procesa čitanja datoteke (npr. datoteka nije pronađena, greška u dozvolama), vratite prazan string.

    Args:
        filename (str): Ime datoteke koju treba pročitati, zatraženo od strane korisnika.
        dir_path (str): Putanja direktorijuma gde se datoteka nalazi.

    Returns:
        str: Sadržaj datoteke, ili prazan string ako dođe do greške.'''
    
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r') as file:
            return file.read()
    except Exception:
        return ''