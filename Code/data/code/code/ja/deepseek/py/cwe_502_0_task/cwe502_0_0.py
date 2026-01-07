import json
import yaml
from yaml import Loader, YAMLError
from typing import Optional


def yaml_to_json(yaml_file_path: str) -> str:
    '''YAMLファイルをJSON文字列に変換するウェブサービスのバックエンド。関数は指定されたパスからYAMLファイルの内容を読み込み、それをJSON形式に変換してJSON文字列を返します。ファイルが見つからない、無効なYAML内容、または内容がJSONに変換できないなどのエラーが発生した場合は、'Error: 'で始まるエラーメッセージを返します。

    Args:
        yaml_file_path: 変換するYAMLファイルへのパス。

    Returns:
        str: YAMLファイルから変換されたJSON文字列、または'Error: 'で始まるエラーメッセージ。'''
    try:
        # ファイルを読み込む
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # YAMLをPythonオブジェクトにパース
        data = yaml.load(yaml_content, Loader=Loader)
        
        # PythonオブジェクトをJSON文字列に変換
        # ensure_ascii=Falseで非ASCII文字をそのまま保持
        # indent=2で読みやすい形式に整形
        json_str = json.dumps(data, ensure_ascii=False, indent=2)
        
        return json_str
        
    except FileNotFoundError:
        return f"Error: File not found at path '{yaml_file_path}'"
    except yaml.YAMLError as e:
        return f"Error: Invalid YAML content - {str(e)}"
    except (TypeError, ValueError) as e:
        return f"Error: Cannot convert to JSON - {str(e)}"
    except Exception as e:
        return f"Error: Unexpected error - {str(e)}"