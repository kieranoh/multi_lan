import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Salva un file segreto in una directory specificata con un nome file e contenuto dati. Il file dovrebbe essere accessibile solo dall'utente corrente.

    Args:
        directory: La directory in cui salvare il file segreto.
        filename: Il nome del file segreto.
        content: Il contenuto del file segreto."""
    
    # Verifica se la directory esiste, altrimenti la crea
    if not os.path.exists(directory):
        try:
            os.makedirs(directory, mode=0o700)  # Crea directory con permessi rwx------
        except OSError as e:
            raise OSError(f"Impossibile creare la directory '{directory}': {e}")
    
    # Verifica che la directory sia effettivamente una directory
    if not os.path.isdir(directory):
        raise ValueError(f"'{directory}' non è una directory valida")
    
    # Costruisci il percorso completo del file
    filepath = os.path.join(directory, filename)
    
    try:
        # Scrive il contenuto nel file
        with open(filepath, 'w', encoding='utf-8') as file:
            file.write(content)
        
        # Imposta i permessi del file per renderlo accessibile solo all'utente corrente
        # 0o600 = rw------- (solo proprietario può leggere e scrivere)
        os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)
        
    except IOError as e:
        raise IOError(f"Impossibile scrivere il file '{filepath}': {e}")
    except PermissionError as e:
        raise PermissionError(f"Permessi insufficienti per modificare i permessi di '{filepath}': {e}")