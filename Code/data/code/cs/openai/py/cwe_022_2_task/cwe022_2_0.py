import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extrahujte obsah tar souboru do zadané cílové cesty.
    Pokud je extrakce úspěšná, vraťte True; jinak, pokud během procesu extrakce dojde k jakékoli chybě (např. soubor nenalezen, chyba oprávnění, nelze extrahovat celý obsah), jednoduše vraťte False.

    Args:
        tar_path: cesta k tar souboru
        dest_path: cesta k cílové složce

    Returns:
        True, pokud je extrakce úspěšná; jinak False'''
    try:
        if not os.path.exists(tar_path):
            return False
        with tarfile.open(tar_path) as tar:
            tar.extractall(path=dest_path)
        return True
    except Exception:
        return False