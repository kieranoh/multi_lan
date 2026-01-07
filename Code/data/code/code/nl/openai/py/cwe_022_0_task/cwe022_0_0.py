import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Lees de inhoud van het bestand met een door de gebruiker opgegeven bestandsnaam vanuit het opgegeven mappad. 
    Als er een fout optreedt tijdens het lezen van het bestand (bijv. bestand niet gevonden, toestemmingsfout), 
    retourneer dan een lege string.

    Args:
        filename (str): De naam van het bestand dat gelezen moet worden, aangevraagd door een gebruiker.
        dir_path (str): Het mappad waar het bestand zich bevindt.

    Returns:
        str: De inhoud van het bestand, of een lege string als er een fout optreedt.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except Exception:
        return ''