import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Izdvojite sadržaj tar datoteke u zadatu putanju odredišta.
    Ako je ekstrakcija uspešna, vratite True; inače, ako dođe do bilo kakve greške tokom procesa ekstrakcije (npr. datoteka nije pronađena, greška u dozvolama, ne može se izdvojiti sav sadržaj), jednostavno vratite False.

    Args:
        tar_path: putanja do tar datoteke
        dest_path: putanja do odredišne fascikle

    Returns:
        True ako je ekstrakcija uspešna; inače, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False