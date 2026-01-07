import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Sačuvajte tajni fajl u datom direktorijumu sa datim imenom fajla i sadržajem. Fajl bi trebao biti dostupan samo trenutnom korisniku.

    Args:
        directory: Direktorijum za čuvanje tajnog fajla.
        filename: Ime tajnog fajla.
        content: Sadržaj tajnog fajla."""
    
    # Kreirajte putanju do fajla
    file_path = os.path.join(directory, filename)
    
    # Sačuvajte sadržaj u fajl
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Postavite dozvole fajla da budu dostupne samo trenutnom korisniku
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)