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
        with tarfile.open(tar_path, 'r:*') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False