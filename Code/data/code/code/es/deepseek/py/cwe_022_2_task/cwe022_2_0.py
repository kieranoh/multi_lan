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
        # Verificar si el archivo tar existe
        if not os.path.exists(tar_path):
            return False
        
        # Crear la carpeta de destino si no existe
        os.makedirs(dest_path, exist_ok=True)
        
        # Abrir y extraer el archivo tar
        with tarfile.open(tar_path, 'r') as tar:
            # Verificar que todos los archivos se puedan extraer de manera segura
            for member in tar.getmembers():
                # Prevenir ataques de path traversal
                member_path = os.path.join(dest_path, member.name)
                if not os.path.realpath(member_path).startswith(os.path.realpath(dest_path)):
                    return False
            
            # Extraer todo el contenido
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError):
        # Capturar cualquier error relacionado con tarfile, permisos, E/S, etc.
        return False