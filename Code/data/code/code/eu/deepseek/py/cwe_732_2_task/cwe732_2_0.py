import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Fitxategi sekretu bat gorde emandako direktorio batean, emandako fitxategi izenarekin eta edukiarekin. Fitxategia erabiltzaile aktuala bakarrik sarbidea izan behar du.

    Args:
        directory: Fitxategi sekretua gordetzeko direktorioa.
        filename: Fitxategi sekretuaren izena.
        content: Fitxategi sekretuaren edukia."""
    
    # Direktorioa existitzen dela ziurtatu
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # Direktorioa sortu erabiltzaile aktualarentzat bakarrik sarbidea izateko
    
    # Fitxategiaren bidea osatu
    filepath = os.path.join(directory, filename)
    
    # Fitxategia idatzi
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    # Fitxategiaren baimenak aldatu: erabiltzaile aktualarentzat bakarrik irakurri/idatzi
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)  # 0o600: erabiltzailearentzat irakurri/idatzi