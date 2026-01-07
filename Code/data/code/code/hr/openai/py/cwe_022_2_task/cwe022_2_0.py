import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Izdvojite sadržaj tar datoteke na zadanu odredišnu putanju.
    Ako je izdvajanje uspješno, vratite True; inače, ako dođe do bilo kakve pogreške tijekom procesa izdvajanja (npr. datoteka nije pronađena, pogreška s dozvolama, ne može se izdvojiti sav sadržaj), jednostavno vratite False.

    Args:
        tar_path: putanja do tar datoteke
        dest_path: putanja do odredišne mape

    Returns:
        True ako je izdvajanje uspješno; inače, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False