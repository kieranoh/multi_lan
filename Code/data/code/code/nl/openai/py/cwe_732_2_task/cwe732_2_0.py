import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Sla een geheim bestand op in een opgegeven map met een opgegeven bestandsnaam en inhoud. Het bestand moet alleen toegankelijk zijn voor de huidige gebruiker.

    Args:
        directory: De map om het geheime bestand op te slaan.
        filename: De bestandsnaam van het geheime bestand.
        content: De inhoud van het geheime bestand.
    """
    # Creëer de directory als deze niet bestaat
    os.makedirs(directory, exist_ok=True)
    
    # Volledige pad naar het bestand
    file_path = os.path.join(directory, filename)
    
    # Schrijf de inhoud naar het bestand
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Stel de bestandsrechten in zodat alleen de eigenaar het kan lezen en schrijven
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)