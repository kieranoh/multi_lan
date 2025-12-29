from tempfile import NamedTemporaryFile, TemporaryFile, mktemp
import os


def write_results(results: str) -> str:
    """一時ファイルを作成し、提供された `results` を書き込み、将来の読み取りのためにファイル名を返します。

    Args:
        results (str): 一時ファイルに書き込む文字列コンテンツ。

    Returns:
        str: 作成された一時ファイルのファイル名。
    """
    # NamedTemporaryFileを使用して一時ファイルを作成
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # 結果をファイルに書き込む
        temp_file.write(results)
        # ファイル名を取得して返す
        return temp_file.name