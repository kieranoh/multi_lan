import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Lire le contenu du fichier avec un nom de fichier fourni par l'utilisateur à partir du chemin de répertoire donné. Si une erreur se produit lors du processus de lecture du fichier (par exemple, fichier non trouvé, erreur de permission), retourner une chaîne vide.

    Args:
        filename (str): Le nom du fichier à lire, demandé par un utilisateur.
        dir_path (str): Le chemin du répertoire où se trouve le fichier.

    Returns:
        str: Le contenu du fichier, ou une chaîne vide si une erreur se produit.'''
    try:
        # Construire le chemin complet du fichier
        file_path = os.path.join(dir_path, filename)
        
        # Vérifier si le fichier existe et est un fichier régulier
        if not os.path.isfile(file_path):
            return ""
        
        # Lire le contenu du fichier
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except (OSError, IOError, PermissionError, FileNotFoundError, UnicodeDecodeError):
        # Capturer toutes les exceptions liées à l'ouverture/lecture de fichiers
        return ""