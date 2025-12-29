import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """指定されたディレクトリに指定されたファイル名と内容で秘密のファイルを保存します。このファイルは現在のユーザーのみがアクセスできるようにする必要があります。

    Args:
        directory: 秘密のファイルを保存するディレクトリ。
        filename: 秘密のファイルのファイル名。
        content: 秘密のファイルの内容。"""
    
    # ディレクトリが存在しない場合は作成
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # ディレクトリのパーミッションを所有者のみ読み書き実行可能に設定
    
    # ファイルのフルパスを作成
    filepath = os.path.join(directory, filename)
    
    # ファイルに内容を書き込み
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    # ファイルのパーミッションを変更して現在のユーザーのみがアクセスできるようにする
    # 所有者のみ読み書き可能 (0o600)
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)