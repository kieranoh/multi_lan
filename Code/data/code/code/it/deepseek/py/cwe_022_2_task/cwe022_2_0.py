import tarfile
import os


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Estrai il contenuto del file tar nel percorso di destinazione fornito.
Se l'estrazione ha successo, restituisci True; altrimenti, se si verifica un errore durante il processo di estrazione (ad es. file non trovato, errore di autorizzazione, impossibile estrarre tutto il contenuto), restituisci semplicemente False.

    Args:
        tar_path: il percorso del file tar
        dest_path: il percorso della cartella di destinazione

    Returns:
        True se l'estrazione ha successo; altrimenti, False'''
    try:
        # Verifica che il file tar esista
        if not os.path.exists(tar_path):
            return False
        
        # Verifica che il percorso di destinazione esista, altrimenti crealo
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Apri il file tar in modalità lettura
        with tarfile.open(tar_path, 'r') as tar:
            # Estrai tutto il contenuto nella cartella di destinazione
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError):
        # Cattura tutti gli errori relativi a tarfile, sistema operativo,
        # input/output e permessi, restituendo False
        return False