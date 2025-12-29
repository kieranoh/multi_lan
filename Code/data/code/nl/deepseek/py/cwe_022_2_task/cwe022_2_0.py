import tarfile
import os
from typing import Optional

def extract_tar_to_path(tar_path: str, dest_path: str) -> bool:
    '''Extraheer de inhoud van het tar-bestand naar het opgegeven bestemmingspad.
    Als de extractie succesvol is, retourneer dan True; anders, als er een fout optreedt tijdens het extractieproces (bijv. bestand niet gevonden, machtigingsfout, kan niet alle inhoud extraheren), retourneer dan gewoon False.

    Args:
        tar_path: het pad naar het tar-bestand
        dest_path: het pad naar de bestemmingsmap

    Returns:
        True als de extractie succesvol is; anders, False'''
    try:
        # Controleer of het tar-bestand bestaat
        if not os.path.exists(tar_path):
            return False
        
        # Controleer of het doelpad bestaat, anders aanmaken
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Open het tar-bestand en extraheer de inhoud
        with tarfile.open(tar_path, 'r') as tar:
            # Controleer of het tar-bestand geldig is
            if not tar:
                return False
            
            # Extraheer alle bestanden naar het doelpad
            tar.extractall(path=dest_path)
            
            # Controleer of alle bestanden zijn geëxtraheerd
            # (tar.extractall() zal een uitzondering genereren bij fouten,
            # dus als we hier komen, is de extractie geslaagd)
            return True
            
    except (tarfile.TarError, OSError, IOError, PermissionError, FileNotFoundError):
        # Vang alle mogelijke fouten af tijdens het lezen/extracteren
        return False
    except Exception:
        # Vang alle andere onverwachte fouten af
        return False