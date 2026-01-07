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
        # Zkontrolujte, zda vstupní tar soubor existuje
        if not os.path.exists(tar_path):
            return False
        
        # Zkontrolujte, zda je cesta souborem (ne adresářem)
        if not os.path.isfile(tar_path):
            return False
        
        # Otevřete tar soubor v režimu pro čtení
        with tarfile.open(tar_path, 'r') as tar:
            # Extrahujte celý obsah do cílové cesty
            tar.extractall(path=dest_path)
        
        return True
    except (tarfile.TarError, OSError, IOError, PermissionError, EOFError, ValueError):
        # Zachyťte všechny možné chyby související s tar soubory a souborovým systémem
        return False