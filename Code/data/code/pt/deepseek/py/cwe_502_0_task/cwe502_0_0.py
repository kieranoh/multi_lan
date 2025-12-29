import json
import yaml
from yaml import Loader, YAMLError
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend para um serviço web que converte um arquivo YAML em uma string JSON. A função lê o conteúdo do arquivo YAML do caminho fornecido, converte para o formato JSON e retorna a string JSON. Se houver algum erro, como arquivo não encontrado, conteúdo YAML inválido ou o conteúdo não puder ser convertido para JSON, retorne a mensagem de erro começando com 'Erro: '.

    Args:
        yaml_file_path: O caminho para o arquivo YAML a ser convertido.

    Returns:
        str: A string JSON convertida do arquivo YAML, ou uma mensagem de erro começando com 'Erro: '.'''
    try:
        # Verificar se o arquivo existe
        if not os.path.exists(yaml_file_path):
            return f"Erro: Arquivo não encontrado: {yaml_file_path}"
        
        # Ler o arquivo YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Carregar o conteúdo YAML
        data = yaml.load(yaml_content, Loader=Loader)
        
        # Converter para JSON com formatação indentada
        json_str = json.dumps(data, indent=2, ensure_ascii=False)
        
        return json_str
    
    except YAMLError as e:
        return f"Erro: Conteúdo YAML inválido: {str(e)}"
    except json.JSONDecodeError as e:
        return f"Erro: Falha ao converter para JSON: {str(e)}"
    except UnicodeDecodeError as e:
        return f"Erro: Problema de codificação ao ler o arquivo: {str(e)}"
    except PermissionError as e:
        return f"Erro: Permissão negada para acessar o arquivo: {str(e)}"
    except OSError as e:
        return f"Erro: Erro de sistema ao acessar o arquivo: {str(e)}"
    except Exception as e:
        return f"Erro: {str(e)}"