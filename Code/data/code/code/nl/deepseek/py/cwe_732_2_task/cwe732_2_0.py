import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Sla een geheim bestand op in een opgegeven map met een opgegeven bestandsnaam en inhoud. Het bestand moet alleen toegankelijk zijn voor de huidige gebruiker.

    Args:
        directory: De map om het geheime bestand op te slaan.
        filename: De bestandsnaam van het geheime bestand.
        content: De inhoud van het geheime bestand.
    """
    # Controleer of de directory bestaat, zo niet maak deze aan
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # Alleen toegankelijk voor de huidige gebruiker
    
    # Volledig pad naar het bestand
    file_path = os.path.join(directory, filename)
    
    # Schrijf de inhoud naar het bestand
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Stel bestandspermissies in zodat alleen de huidige gebruiker toegang heeft
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)  # Alleen lees- en schrijfrechten voor de eigenaar