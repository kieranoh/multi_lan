import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Crea un fitxer temporal, escriu els `resultats` proporcionats i retorna el nom del fitxer per a futures lectures.

    Args:
        results (str): El contingut de cadena a escriure al fitxer temporal.

    Returns:
        str: El nom del fitxer del fitxer temporal creat."""
    # Utilitzem NamedTemporaryFile per crear un fitxer temporal amb nom
    # delete=False assegura que el fitxer no s'elimini automàticament quan es tanqui
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        temp_file.write(results)
        # Retornem el nom del fitxer per a futures lectures
        return temp_file.name