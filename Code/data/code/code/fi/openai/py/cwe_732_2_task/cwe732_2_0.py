import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Tallenna salainen tiedosto annettuun hakemistoon annetulla tiedostonimellä ja sisällöllä. Tiedoston tulisi olla vain nykyisen käyttäjän saatavilla.

    Args:
        directory: Hakemisto, johon salainen tiedosto tallennetaan.
        filename: Salaisen tiedoston nimi.
        content: Salaisen tiedoston sisältö.
    """
    # Varmistetaan, että hakemisto olemassa
    os.makedirs(directory, exist_ok=True)

    # Määritetään tiedoston polku
    file_path = os.path.join(directory, filename)

    # Tallennetaan sisältö tiedostoon
    with open(file_path, 'w') as file:
        file.write(content)

    # Muutetaan tiedoston käyttöoikeuksia niin, että vain omistaja voi lukea tai kirjoittaa
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)