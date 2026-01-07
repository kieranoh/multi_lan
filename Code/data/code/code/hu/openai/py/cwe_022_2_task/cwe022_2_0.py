import tarfile

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Kicsomagolja a tar fájl tartalmát a megadott célútvonalra.
    Ha a kicsomagolás sikeres, térjen vissza True értékkel; különben, ha bármilyen hiba lép fel a kicsomagolás során (pl. fájl nem található, jogosultsági hiba, nem lehet az összes tartalmat kicsomagolni), egyszerűen térjen vissza False értékkel.

    Args:
        tar_path: a tar fájl elérési útja
        dest_path: a célmappa elérési útja

    Returns:
        True, ha a kicsomagolás sikeres; különben False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except Exception:
        return False