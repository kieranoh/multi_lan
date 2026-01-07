import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extrahera innehållet i tar-filen till den angivna destinationsvägen.
    Om extraktionen är framgångsrik, returnera True; annars, om något fel uppstår under extraktionsprocessen (t.ex. filen hittades inte, behörighetsfel, kan inte extrahera allt innehåll), returnera bara False.

    Args:
        tar_path: sökvägen till tar-filen
        dest_path: sökvägen till destinationsmappen

    Returns:
        True om extraktionen är framgångsrik; annars, False'''
    try:
        # Kontrollera om tar-filen finns
        if not os.path.exists(tar_path):
            return False
        
        # Kontrollera om destinationsmappen finns, skapa den om den inte finns
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Öppna och extrahera tar-filen
        with tarfile.open(tar_path, 'r') as tar:
            # Extrahera allt innehåll till destinationsmappen
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError):
        # Fånga alla fel relaterade till tar-filer, filsystem och behörigheter
        return False