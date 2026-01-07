import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Salva un file segreto in una directory specificata con un nome file e contenuto dati. Il file dovrebbe essere accessibile solo dall'utente corrente.

    Args:
        directory: La directory in cui salvare il file segreto.
        filename: Il nome del file segreto.
        content: Il contenuto del file segreto."""
    
    # Creare il percorso completo del file
    file_path = os.path.join(directory, filename)
    
    # Scrivere il contenuto nel file
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Impostare i permessi del file per renderlo accessibile solo all'utente corrente
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)