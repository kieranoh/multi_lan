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
        # Verificar si el fitxer tar existeix
        if not os.path.exists(tar_path):
            return False
        
        # Verificar si la ruta de destinació existeix, si no, crear-la
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Obrir el fitxer tar i extreure el contingut
        with tarfile.open(tar_path, 'r') as tar:
            # Verificar que es pugui llegir el fitxer tar
            tar.getmembers()  # Això llançarà una excepció si el fitxer està corrupte o no es pot llegir
            
            # Extreure tot el contingut a la ruta de destinació
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError, FileNotFoundError):
        # Capturar qualsevol error relacionat amb tarfile, permisos, fitxer no trobat, etc.
        return False