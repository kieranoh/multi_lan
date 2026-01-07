import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Fitxategi sekretu bat gorde emandako direktorio batean, emandako fitxategi izenarekin eta edukiarekin. Fitxategia erabiltzaile aktuala bakarrik sarbidea izan behar du.

    Args:
        directory: Fitxategi sekretua gordetzeko direktorioa.
        filename: Fitxategi sekretuaren izena.
        content: Fitxategi sekretuaren edukia."""
    
    # Fitxategiaren bidea osatu
    file_path = os.path.join(directory, filename)
    
    # Edukia fitxategian idatzi
    with open(file_path, 'w') as secret_file:
        secret_file.write(content)
    
    # Fitxategia irakurri eta idazteko baimena kendu
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)
    # Beste erabiltzaileek irakurri eta idazteko baimena izan ez dezaten
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)