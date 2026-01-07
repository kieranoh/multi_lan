import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Maak een tijdelijk bestand, schrijf de opgegeven `results` erin en retourneer de bestandsnaam voor toekomstig lezen.

    Args:
        results (str): De stringinhoud die in het tijdelijke bestand moet worden geschreven.

    Returns:
        str: De bestandsnaam van het gemaakte tijdelijke bestand.
    """
    # Maak een NamedTemporaryFile in schrijfmodus ('w') met tekstmodus (default)
    # delete=False zorgt ervoor dat het bestand niet automatisch wordt verwijderd bij sluiten
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Schrijf de resultaten naar het tijdelijke bestand
        temp_file.write(results)
        # Retourneer de bestandsnaam van het tijdelijke bestand
        return temp_file.name