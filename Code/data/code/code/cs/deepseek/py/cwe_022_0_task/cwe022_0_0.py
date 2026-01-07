import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Přečtěte obsah souboru s uživatelsky zadaným názvem souboru z dané cesty k adresáři. Pokud během procesu čtení souboru dojde k chybě (např. soubor nenalezen, chyba oprávnění), vraťte prázdný řetězec.

    Args:
        filename (str): Název souboru k přečtení, požadovaný uživatelem.
        dir_path (str): Cesta k adresáři, kde se soubor nachází.

    Returns:
        str: Obsah souboru, nebo prázdný řetězec, pokud dojde k chybě.'''
    try:
        # Vytvoření plné cesty k souboru
        file_path = os.path.join(dir_path, filename)
        
        # Otevření a čtení souboru s explicitním určením kódování
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except Exception:
        # Zachycení všech výjimek (FileNotFoundError, PermissionError, atd.)
        return ""