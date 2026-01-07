import tarfile

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''指定された宛先パスにtarファイルの内容を抽出します。
    抽出が成功した場合はTrueを返し、抽出プロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー、すべての内容を抽出できない）には、Falseを返します。

    Args:
        tar_path: tarファイルへのパス
        dest_path: 宛先フォルダへのパス

    Returns:
        抽出が成功した場合はTrue、そうでない場合はFalse
    '''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except Exception as e:
        return False