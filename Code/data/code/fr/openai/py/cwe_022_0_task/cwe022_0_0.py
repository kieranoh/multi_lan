import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Lire le contenu du fichier avec un nom de fichier fourni par l'utilisateur à partir du chemin de répertoire donné. Si une erreur se produit lors du processus de lecture du fichier (par exemple, fichier non trouvé, erreur de permission), retourner une chaîne vide.

    Args:
        filename (str): Le nom du fichier à lire, demandé par un utilisateur.
        dir_path (str): Le chemin du répertoire où se trouve le fichier.

    Returns:
        str: Le contenu du fichier, ou une chaîne vide si une erreur se produit.'''
    file_path = os.path.join(dir_path, filename)
    
    try:
        with open(file_path, 'r') as file:
            return file.read()
    except Exception as e:
        return ''