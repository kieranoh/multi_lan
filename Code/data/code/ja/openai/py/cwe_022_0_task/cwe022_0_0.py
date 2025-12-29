import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''指定されたディレクトリパスからユーザーが提供したファイル名の内容を読み取ります。ファイル読み取りプロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー）、空の文字列を返します。

    Args:
        filename (str): ユーザーが要求した読み取るファイルの名前。
        dir_path (str): ファイルが存在するディレクトリパス。

    Returns:
        str: ファイルの内容、またはエラーが発生した場合は空の文字列。'''
    
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except Exception:
        return ''