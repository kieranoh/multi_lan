from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """Luo väliaikainen tiedosto, kirjoita annettu `results` siihen ja palauta tiedoston nimi tulevaa lukemista varten.

    Args:
        results (str): Merkkijono, joka kirjoitetaan väliaikaiseen tiedostoon.

    Returns:
        str: Luodun väliaikaisen tiedoston nimi.
    """
    # Luodaan väliaikainen tiedosto, joka ei poistu automaattisesti suljettaessa
    # 'delete=False' varmistaa, että tiedosto säilyy palautetun nimen kautta käytettävissä
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Kirjoitetaan results-merkkijono tiedostoon
        temp_file.write(results)
        # Palautetaan tiedoston polku
        return temp_file.name