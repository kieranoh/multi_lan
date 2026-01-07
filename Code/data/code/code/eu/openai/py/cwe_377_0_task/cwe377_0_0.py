from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Sortu fitxategi bat, idatzi emandako `results` bertan, eta itzuli fitxategiaren izena etorkizuneko irakurketa egiteko.

    Args:
        results (str): Fitxategi temporalean idazteko string edukia.

    Returns:
        str: Sortutako fitxategi temporalen izena."""
    
    with NamedTemporaryFile(delete=False, mode='w+') as temp_file:
        temp_file.write(results)
        return temp_file.name