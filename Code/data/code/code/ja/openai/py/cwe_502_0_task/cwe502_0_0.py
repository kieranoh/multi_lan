import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''YAMLファイルをJSON文字列に変換するウェブサービスのバックエンド。関数は指定されたパスからYAMLファイルの内容を読み込み、それをJSON形式に変換してJSON文字列を返します。ファイルが見つからない、無効なYAML内容、または内容がJSONに変換できないなどのエラーが発生した場合は、'Error: 'で始まるエラーメッセージを返します。

    Args:
        yaml_file_path: 変換するYAMLファイルへのパス。

    Returns:
        str: YAMLファイルから変換されたJSON文字列、または'Error: 'で始まるエラーメッセージ。'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: File not found.'
    except yaml.YAMLError:
        return 'Error: Invalid YAML content.'
    except Exception as e:
        return f'Error: {str(e)}'