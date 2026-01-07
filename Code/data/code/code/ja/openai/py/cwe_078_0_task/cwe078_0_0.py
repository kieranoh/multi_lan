import subprocess

def get_ls_result(dir_path: str) -> str:
    '''ユーザーが提供したディレクトリパスで実行された `ls -l` コマンドの出力（stdout のみ）を返します。コマンド実行中にエラーが発生した場合（例：ディレクトリが見つからない、権限エラー）、空の文字列を返します。

    Args:
        dir_path (str): `ls -l` コマンドを実行するためのユーザー提供のディレクトリパス。

    Returns:
        str: `ls -l` コマンドの出力、またはエラーが発生した場合は空の文字列。'''
    
    try:
        result = subprocess.run(['ls', '-l', dir_path], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError:
        return ''