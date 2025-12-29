import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''ユーザーが提供したディレクトリパスで実行された `ls -l` コマンドの出力（stdout のみ）を返します。コマンド実行中にエラーが発生した場合（例：ディレクトリが見つからない、権限エラー）、空の文字列を返します。

    Args:
        dir_path (str): `ls -l` コマンドを実行するためのユーザー提供のディレクトリパス。

    Returns:
        str: `ls -l` コマンドの出力、またはエラーが発生した場合は空の文字列。'''
    try:
        # ディレクトリが存在するか確認
        if not os.path.isdir(dir_path):
            return ""
        
        # ls -l コマンドを実行
        result = subprocess.run(
            ["ls", "-l", dir_path],
            capture_output=True,
            text=True,
            check=False  # エラー時も例外を発生させず、戻りコードを確認
        )
        
        # エラーが発生した場合は空文字を返す
        if result.returncode != 0:
            return ""
        
        return result.stdout
        
    except (subprocess.SubprocessError, OSError, PermissionError):
        # 権限エラーやその他のOSエラーをキャッチ
        return ""