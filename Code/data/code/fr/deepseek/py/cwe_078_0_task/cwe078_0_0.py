import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''Retourne la sortie (seulement stdout) de la commande `ls -l` lorsqu'elle est exécutée dans un chemin de répertoire fourni par l'utilisateur. Si une erreur se produit pendant l'exécution de la commande (par exemple, répertoire introuvable, erreur de permission), retourne une chaîne vide.

    Args:
        dir_path (str): Le chemin de répertoire fourni par l'utilisateur pour exécuter la commande `ls -l`.

    Returns:
        str: La sortie de la commande `ls -l`, ou une chaîne vide si une erreur se produit.'''
    try:
        # Vérifier si le chemin existe et est un répertoire
        if not os.path.isdir(dir_path):
            return ""
        
        # Exécuter la commande ls -l dans le répertoire spécifié
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # Ne pas lever d'exception automatiquement
        )
        
        # Si le code de retour est différent de 0, considérer comme une erreur
        if result.returncode != 0:
            return ""
        
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Capturer toutes les exceptions liées à l'exécution de la commande
        # ou aux problèmes de permissions
        return ""