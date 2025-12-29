import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend pour un service web qui convertit un fichier YAML en chaîne JSON. La fonction lit le contenu du fichier YAML à partir du chemin donné, le convertit au format JSON et renvoie la chaîne JSON. S'il y a une erreur, comme un fichier introuvable, un contenu YAML invalide ou si le contenu ne peut pas être converti en JSON, renvoie le message d'erreur commençant par 'Erreur : '.

    Args:
        yaml_file_path: Le chemin vers le fichier YAML à convertir.

    Returns:
        str: La chaîne JSON convertie à partir du fichier YAML, ou un message d'erreur commençant par 'Erreur : '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Erreur : Fichier introuvable.'
    except yaml.YAMLError:
        return 'Erreur : Contenu YAML invalide.'
    except json.JSONDecodeError:
        return 'Erreur : Le contenu ne peut pas être converti en JSON.'