from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """一時ファイルを作成し、提供された `results` を書き込み、将来の読み取りのためにファイル名を返します。

    Args:
        results (str): 一時ファイルに書き込む文字列コンテンツ。

    Returns:
        str: 作成された一時ファイルのファイル名。
    """
    with NamedTemporaryFile(delete=False) as temp_file:
        temp_file.write(results.encode('utf-8'))
        return temp_file.name