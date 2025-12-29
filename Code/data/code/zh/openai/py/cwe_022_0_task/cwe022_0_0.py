import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''从给定的目录路径中读取用户提供的文件名的内容。如果在文件读取过程中发生任何错误（例如，文件未找到，权限错误），则返回一个空字符串。

    Args:
        filename (str): 用户请求的要读取的文件名。
        dir_path (str): 文件所在的目录路径。

    Returns:
        str: 文件的内容，如果发生任何错误则返回一个空字符串。'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r') as file:
            return file.read()
    except Exception:
        return ''