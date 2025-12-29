from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Crea un fitxer temporal, escriu els `resultats` proporcionats i retorna el nom del fitxer per a futures lectures.

    Args:
        results (str): El contingut de cadena a escriure al fitxer temporal.

    Returns:
        str: El nom del fitxer del fitxer temporal creat."""
    
    with NamedTemporaryFile(delete=False, mode='w', encoding='utf-8') as temp_file:
        temp_file.write(results)
        return temp_file.name