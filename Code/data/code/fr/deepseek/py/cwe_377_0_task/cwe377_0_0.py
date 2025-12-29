import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Créez un fichier temporaire, écrivez les `results` fournis dedans, et renvoyez le nom du fichier pour une lecture future.

    Args:
        results (str): Le contenu sous forme de chaîne à écrire dans le fichier temporaire.

    Returns:
        str: Le nom du fichier du fichier temporaire créé.
    """
    # Créer un fichier temporaire en mode écriture texte
    # delete=False pour que le fichier ne soit pas supprimé automatiquement à la fermeture
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Écrire le contenu dans le fichier
        temp_file.write(results)
        # Récupérer le nom du fichier
        filename = temp_file.name
    
    return filename