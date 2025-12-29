import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Retourne la sortie (seulement stdout) de la commande `ls -l` lorsqu'elle est exécutée dans un chemin de répertoire fourni par l'utilisateur. Si une erreur se produit pendant l'exécution de la commande (par exemple, répertoire introuvable, erreur de permission), retourne une chaîne vide.

    Args:
        dir_path (str): Le chemin de répertoire fourni par l'utilisateur pour exécuter la commande `ls -l`.

    Returns:
        str: La sortie de la commande `ls -l`, ou une chaîne vide si une erreur se produit.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''
    except Exception:
        return ''