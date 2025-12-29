from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Créez un fichier temporaire, écrivez les `results` fournis dedans, et renvoyez le nom du fichier pour une lecture future.

    Args:
        results (str): Le contenu sous forme de chaîne à écrire dans le fichier temporaire.

    Returns:
        str: Le nom du fichier du fichier temporaire créé."""
    
    with NamedTemporaryFile(delete=False, mode='w+t') as temp_file:
        temp_file.write(results)
        return temp_file.name