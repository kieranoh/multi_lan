import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """创建一个临时文件，将提供的 `results` 写入其中，并返回文件名以供将来读取。

    Args:
        results (str): 要写入临时文件的字符串内容。

    Returns:
        str: 创建的临时文件的文件名。"""
    # 使用 NamedTemporaryFile 创建临时文件，设置 delete=False 以便文件不会自动删除
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # 将结果写入文件
        temp_file.write(results)
        # 获取文件名
        filename = temp_file.name
    
    return filename