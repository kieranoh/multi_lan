from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Luo väliaikainen tiedosto, kirjoita annettu `results` siihen ja palauta tiedoston nimi tulevaa lukemista varten.

    Args:
        results (str): Merkkijono, joka kirjoitetaan väliaikaiseen tiedostoon.

    Returns:
        str: Luodun väliaikaisen tiedoston nimi."""
    with NamedTemporaryFile(delete=False) as temp_file:
        temp_file.write(results.encode('utf-8'))
        return temp_file.name