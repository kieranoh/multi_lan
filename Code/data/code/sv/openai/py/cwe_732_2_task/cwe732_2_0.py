import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Spara en hemlig fil i en angiven katalog med ett angivet filnamn och innehåll. Filen ska endast vara tillgänglig för den nuvarande användaren.

    Args:
        directory: Katalogen för att spara den hemliga filen.
        filename: Filnamnet på den hemliga filen.
        content: Innehållet i den hemliga filen.
    """
    # Skapa den angivna katalogen om den inte redan finns
    os.makedirs(directory, exist_ok=True)
    
    # Fullständig sökväg till den hemliga filen
    file_path = os.path.join(directory, filename)
    
    # Skriv innehållet till filen
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Gör filen endast tillgänglig för den nuvarande användaren
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)