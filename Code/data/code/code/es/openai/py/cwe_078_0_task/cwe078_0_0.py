import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Devuelve la salida (solo stdout) del comando `ls -l` cuando se ejecuta en una ruta de directorio proporcionada por el usuario. Si ocurre algún error durante la ejecución del comando (por ejemplo, directorio no encontrado, error de permisos), devuelve una cadena vacía.

    Args:
        dir_path (str): La ruta de directorio proporcionada por el usuario para ejecutar el comando `ls -l`.

    Returns:
        str: La salida del comando `ls -l`, o una cadena vacía si ocurre algún error.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''