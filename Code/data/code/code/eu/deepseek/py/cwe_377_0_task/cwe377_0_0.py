from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """Sortu fitxategi bat, idatzi emandako `results` bertan, eta itzuli fitxategiaren izena etorkizuneko irakurketa egiteko.

    Args:
        results (str): Fitxategi temporalean idazteko string edukia.

    Returns:
        str: Sortutako fitxategi temporalen izena."""
    # NamedTemporaryFile erabiliz fitxategi temporala sortu, 'delete=False' parametroarekin
    # fitxategia itxi ondoren ez ezabatzeko, izena itzuli ahal izateko
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Emaitzak idatzi fitxategian
        temp_file.write(results)
        # Fitxategiaren izena gorde
        temp_filename = temp_file.name
    
    # Fitxategiaren izena itzuli
    return temp_filename