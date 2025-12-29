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
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False