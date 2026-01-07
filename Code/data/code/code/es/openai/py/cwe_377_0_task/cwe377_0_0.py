from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Crea un archivo temporal, escribe el `results` proporcionado en él y devuelve el nombre del archivo para futuras lecturas.

    Args:
        results (str): El contenido en forma de cadena que se escribirá en el archivo temporal.

    Returns:
        str: El nombre del archivo del archivo temporal creado."""
    
    with NamedTemporaryFile(delete=False, mode='w', suffix='.tmp') as temp_file:
        temp_file.write(results)
        return temp_file.name