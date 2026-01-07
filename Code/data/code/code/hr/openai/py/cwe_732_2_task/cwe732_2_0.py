import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Spremi tajnu datoteku u zadani direktorij s danim imenom datoteke i sadržajem. Datoteka bi trebala biti dostupna samo trenutnom korisniku.

    Args:
        directory: Direktorij za spremanje tajne datoteke.
        filename: Ime tajne datoteke.
        content: Sadržaj tajne datoteke."""
    
    # Stvaranje punog puta do datoteke
    file_path = os.path.join(directory, filename)
    
    # Spremanje sadržaja u datoteku
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Postavljanje dozvola datoteke tako da bude dostupna samo trenutnom korisniku
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)