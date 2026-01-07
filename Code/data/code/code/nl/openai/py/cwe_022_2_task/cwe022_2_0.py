import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extraheer de inhoud van het tar-bestand naar het opgegeven bestemmingspad.
    Als de extractie succesvol is, retourneer dan True; anders, als er een fout optreedt tijdens het extractieproces (bijv. bestand niet gevonden, machtigingsfout, kan niet alle inhoud extraheren), retourneer dan gewoon False.

    Args:
        tar_path: het pad naar het tar-bestand
        dest_path: het pad naar de bestemmingsmap

    Returns:
        True als de extractie succesvol is; anders, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False