import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """将秘密文件保存到指定目录，使用指定的文件名和内容。该文件应仅对当前用户可访问。

    Args:
        directory: 保存秘密文件的目录。
        filename: 秘密文件的文件名。
        content: 秘密文件的内容。
    """
    # 创建目录如果不存在
    os.makedirs(directory, exist_ok=True)
    
    # 创建文件路径
    file_path = os.path.join(directory, filename)
    
    # 保存内容到文件
    with open(file_path, 'w') as file:
        file.write(content)
    
    # 设置文件权限，仅当前用户可访问
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)