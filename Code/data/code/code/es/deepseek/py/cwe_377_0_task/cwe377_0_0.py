import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Crea un archivo temporal, escribe el `results` proporcionado en él y devuelve el nombre del archivo para futuras lecturas.

    Args:
        results (str): El contenido en forma de cadena que se escribirá en el archivo temporal.

    Returns:
        str: El nombre del archivo del archivo temporal creado."""
    # Crear un archivo temporal con modo de escritura y lectura, eliminación automática deshabilitada
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Escribir el contenido proporcionado en el archivo
        temp_file.write(results)
        # Obtener el nombre del archivo
        filename = temp_file.name
    
    return filename