import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Extraire le contenu du fichier tar vers le chemin de destination donné.
    Si l'extraction réussit, retourner True ; sinon, si une erreur se produit pendant le processus d'extraction (par exemple, fichier introuvable, erreur de permission, impossible d'extraire tout le contenu), retourner simplement False.

    Args:
        tar_path: le chemin vers le fichier tar
        dest_path: le chemin vers le dossier de destination

    Returns:
        True si l'extraction réussit ; sinon, False'''
    try:
        # Vérifier si le fichier tar existe
        if not os.path.exists(tar_path):
            return False
        
        # Vérifier si le chemin de destination existe, sinon le créer
        if not os.path.exists(dest_path):
            os.makedirs(dest_path, exist_ok=True)
        
        # Ouvrir et extraire le fichier tar
        with tarfile.open(tar_path, 'r') as tar:
            # Vérifier si le fichier est bien un fichier tar valide
            tar.getmembers()  # Cette ligne peut lever une exception si le fichier n'est pas un tar valide
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError, FileNotFoundError):
        # Capturer toutes les exceptions liées à l'extraction tar, aux permissions, aux fichiers, etc.
        return False