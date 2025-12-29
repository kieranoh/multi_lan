import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend para um serviço web que converte um arquivo YAML em uma string JSON. A função lê o conteúdo do arquivo YAML do caminho fornecido, converte para o formato JSON e retorna a string JSON. Se houver algum erro, como arquivo não encontrado, conteúdo YAML inválido ou o conteúdo não puder ser convertido para JSON, retorne a mensagem de erro começando com 'Erro: '.

    Args:
        yaml_file_path: O caminho para o arquivo YAML a ser convertido.

    Returns:
        str: A string JSON convertida do arquivo YAML, ou uma mensagem de erro começando com 'Erro: '.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Erro: Arquivo não encontrado.'
    except yaml.YAMLError:
        return 'Erro: Conteúdo YAML inválido.'
    except Exception as e:
        return f'Erro: {str(e)}'