import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Leggi il contenuto del file con un nome fornito dall'utente dal percorso della directory dato. Se si verifica un errore durante il processo di lettura del file (ad es. file non trovato, errore di autorizzazione), restituisci una stringa vuota.

    Args:
        filename (str): Il nome del file da leggere, richiesto da un utente.
        dir_path (str): Il percorso della directory in cui si trova il file.

    Returns:
        str: Il contenuto del file, o una stringa vuota se si verifica un errore.'''
    try:
        # Costruisci il percorso completo del file
        file_path = os.path.join(dir_path, filename)
        
        # Verifica che il percorso sia un file e non una directory
        if not os.path.isfile(file_path):
            return ""
        
        # Apri e leggi il file
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except (FileNotFoundError, PermissionError, OSError, IOError):
        # Cattura tutti gli errori comuni di I/O e restituisce stringa vuota
        return ""