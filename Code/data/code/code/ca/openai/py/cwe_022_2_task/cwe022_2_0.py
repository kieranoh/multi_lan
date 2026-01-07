import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extreu el contingut del fitxer tar a la ruta de destinació donada.
    Si l'extracció és exitosa, torneu True; d'altra banda, si es produeix algun error durant el procés d'extracció (per exemple, fitxer no trobat, error de permís, no es pot extreure tot el contingut), torneu simplement False.

    Args:
        tar_path: la ruta al fitxer tar
        dest_path: la ruta a la carpeta de destinació

    Returns:
        True si l'extracció és exitosa; d'altra banda, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False