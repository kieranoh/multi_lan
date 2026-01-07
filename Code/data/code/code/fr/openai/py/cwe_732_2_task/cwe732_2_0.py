import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Enregistrez un fichier secret dans un répertoire donné avec un nom de fichier et un contenu spécifiés. Le fichier ne doit être accessible que par l'utilisateur actuel.

    Args:
        directory: Le répertoire pour enregistrer le fichier secret.
        filename: Le nom du fichier secret.
        content: Le contenu du fichier secret."""
    
    # Créer le chemin complet du fichier
    file_path = os.path.join(directory, filename)
    
    # Écrire le contenu dans le fichier
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Modifier les permissions du fichier pour qu'il soit accessible uniquement par l'utilisateur
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)