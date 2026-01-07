import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extrae el contenido del archivo tar a la ruta de destino dada.
    Si la extracción es exitosa, devuelve True; de lo contrario, si ocurre algún error durante el proceso de extracción (por ejemplo, archivo no encontrado, error de permisos, no se puede extraer todo el contenido), simplemente devuelve False.

    Args:
        tar_path: la ruta al archivo tar
        dest_path: la ruta a la carpeta de destino

    Returns:
        True si la extracción es exitosa; de lo contrario, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False