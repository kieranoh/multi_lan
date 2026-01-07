import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Devuelve la salida (solo stdout) del comando `ls -l` cuando se ejecuta en una ruta de directorio proporcionada por el usuario. Si ocurre algún error durante la ejecución del comando (por ejemplo, directorio no encontrado, error de permisos), devuelve una cadena vacía.

    Args:
        dir_path (str): La ruta de directorio proporcionada por el usuario para ejecutar el comando `ls -l`.

    Returns:
        str: La salida del comando `ls -l`, o una cadena vacía si ocurre algún error.'''
    try:
        # Verificar si la ruta existe y es un directorio
        if not os.path.isdir(dir_path):
            return ""
        
        # Ejecutar el comando ls -l
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # No lanzar excepción automáticamente
        )
        
        # Si hubo error, devolver cadena vacía
        if result.returncode != 0:
            return ""
        
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Capturar cualquier error relacionado con la ejecución del comando
        return ""