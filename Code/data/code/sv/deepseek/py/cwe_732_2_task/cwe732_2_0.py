import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Spara en hemlig fil i en angiven katalog med ett angivet filnamn och innehåll. Filen ska endast vara tillgänglig för den nuvarande användaren.

    Args:
        directory: Katalogen för att spara den hemliga filen.
        filename: Filnamnet på den hemliga filen.
        content: Innehållet i den hemliga filen."""
    
    # Skapa katalogen om den inte finns
    os.makedirs(directory, exist_ok=True)
    
    # Sätt rätt behörigheter på katalogen (endast aktuell användare)
    os.chmod(directory, stat.S_IRWXU)
    
    # Skapa fullständig sökväg
    filepath = os.path.join(directory, filename)
    
    # Skriv innehållet till filen
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    # Sätt rätt behörigheter på filen (endast läs- och skrivrättigheter för aktuell användare)
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)