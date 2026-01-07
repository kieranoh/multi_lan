import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """将秘密文件保存到指定目录，使用指定的文件名和内容。该文件应仅对当前用户可访问。

    Args:
        directory: 保存秘密文件的目录。
        filename: 秘密文件的文件名。
        content: 秘密文件的内容。"""
    
    # 确保目录存在
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # 创建目录时设置权限为仅当前用户可访问
    
    # 构建完整的文件路径
    filepath = os.path.join(directory, filename)
    
    # 写入文件内容
    with open(filepath, 'w') as f:
        f.write(content)
    
    # 设置文件权限为仅当前用户可读可写
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)