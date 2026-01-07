import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Pročitajte sadržaj datoteke s imenom koje je korisnik dao iz zadanog putanjskog direktorija. Ako dođe do bilo kakve pogreške tijekom procesa čitanja datoteke (npr. datoteka nije pronađena, pogreška s dozvolama), vratite praznu string.

    Args:
        filename (str): Ime datoteke koju treba pročitati, zatraženo od korisnika.
        dir_path (str): Putanja direktorija gdje se datoteka nalazi.

    Returns:
        str: Sadržaj datoteke, ili prazna string ako dođe do bilo kakve pogreške.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r') as file:
            return file.read()
    except Exception:
        return ''