from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """创建一个临时文件，将提供的 `results` 写入其中，并返回文件名以供将来读取。

    Args:
        results (str): 要写入临时文件的字符串内容。

    Returns:
        str: 创建的临时文件的文件名。
    """
    with NamedTemporaryFile(delete=False) as tmp_file:
        tmp_file.write(results.encode('utf-8'))
        return tmp_file.name