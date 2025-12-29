import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Lee el contenido del archivo con un nombre de archivo proporcionado por el usuario desde la ruta de directorio dada. Si ocurre algún error durante el proceso de lectura del archivo (por ejemplo, archivo no encontrado, error de permisos), devuelve una cadena vacía.

    Args:
        filename (str): El nombre del archivo a leer, solicitado por un usuario.
        dir_path (str): La ruta del directorio donde se encuentra el archivo.

    Returns:
        str: El contenido del archivo, o una cadena vacía si ocurre algún error.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r') as file:
            return file.read()
    except Exception:
        return ''