import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Enregistrez un fichier secret dans un répertoire donné avec un nom de fichier et un contenu spécifiés. Le fichier ne doit être accessible que par l'utilisateur actuel.

    Args:
        directory: Le répertoire pour enregistrer le fichier secret.
        filename: Le nom du fichier secret.
        content: Le contenu du fichier secret."""
    
    # Vérifier si le répertoire existe, sinon le créer
    if not os.path.exists(directory):
        try:
            os.makedirs(directory, mode=0o700)  # Créer avec permissions uniquement pour l'utilisateur
        except OSError as e:
            raise OSError(f"Impossible de créer le répertoire {directory}: {e}")
    
    # Vérifier que le répertoire est accessible en écriture
    if not os.access(directory, os.W_OK):
        raise PermissionError(f"Pas de permission d'écriture dans le répertoire {directory}")
    
    # Construire le chemin complet du fichier
    filepath = os.path.join(directory, filename)
    
    try:
        # Écrire le contenu dans le fichier
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        
        # Modifier les permissions du fichier pour qu'il ne soit accessible que par l'utilisateur actuel
        os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)  # Lecture et écriture uniquement pour le propriétaire
        
    except IOError as e:
        raise IOError(f"Erreur lors de l'écriture du fichier {filepath}: {e}")
    except OSError as e:
        raise OSError(f"Erreur lors de la modification des permissions du fichier {filepath}: {e}")