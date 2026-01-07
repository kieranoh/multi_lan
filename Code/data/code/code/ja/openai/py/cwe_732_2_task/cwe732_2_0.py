import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """指定されたディレクトリに指定されたファイル名と内容で秘密のファイルを保存します。このファイルは現在のユーザーのみがアクセスできるようにする必要があります。

    Args:
        directory: 秘密のファイルを保存するディレクトリ。
        filename: 秘密のファイルのファイル名。
        content: 秘密のファイルの内容。
    """
    # ディレクトリが存在しない場合は作成
    os.makedirs(directory, exist_ok=True)
    
    # ファイルパスを作成
    file_path = os.path.join(directory, filename)
    
    # 内容を書き込む
    with open(file_path, 'w') as file:
        file.write(content)
    
    # ファイルのアクセス権を変更して、現在のユーザーのみがアクセスできるようにする
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)