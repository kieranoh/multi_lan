import json
import yaml
from yaml import Loader
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend pour un service web qui convertit un fichier YAML en chaîne JSON. La fonction lit le contenu du fichier YAML à partir du chemin donné, le convertit au format JSON et renvoie la chaîne JSON. S'il y a une erreur, comme un fichier introuvable, un contenu YAML invalide ou si le contenu ne peut pas être converti en JSON, renvoie le message d'erreur commençant par 'Erreur : '.

    Args:
        yaml_file_path: Le chemin vers le fichier YAML à convertir.

    Returns:
        str: La chaîne JSON convertie à partir du fichier YAML, ou un message d'erreur commençant par 'Erreur : '.'''
    try:
        # Vérifier si le fichier existe
        if not os.path.exists(yaml_file_path):
            return f"Erreur : Le fichier '{yaml_file_path}' est introuvable."
        
        # Vérifier si c'est un fichier
        if not os.path.isfile(yaml_file_path):
            return f"Erreur : '{yaml_file_path}' n'est pas un fichier valide."
        
        # Lire le contenu du fichier YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Vérifier si le fichier est vide
        if not yaml_content.strip():
            return "Erreur : Le fichier YAML est vide."
        
        # Convertir YAML en objet Python
        python_obj = yaml.load(yaml_content, Loader=Loader)
        
        # Convertir l'objet Python en chaîne JSON
        json_str = json.dumps(python_obj, ensure_ascii=False, indent=2)
        
        return json_str
        
    except yaml.YAMLError as e:
        return f"Erreur : Contenu YAML invalide - {str(e)}"
    except json.JSONEncodeError as e:
        return f"Erreur : Impossible de convertir en JSON - {str(e)}"
    except UnicodeDecodeError:
        return f"Erreur : Impossible de décoder le fichier avec l'encodage UTF-8."
    except PermissionError:
        return f"Erreur : Permission refusée pour lire le fichier '{yaml_file_path}'."
    except Exception as e:
        return f"Erreur : {str(e)}"