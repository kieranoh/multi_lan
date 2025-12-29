import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''将 tar 文件的内容提取到给定的目标路径。如果提取成功，返回 True；否则，如果在提取过程中发生任何错误（例如，文件未找到、权限错误、无法提取所有内容），则返回 False。

    Args:
        tar_path: tar 文件的路径
        dest_path: 目标文件夹的路径

    Returns:
        如果提取成功则返回 True；否则返回 False'''
    try:
        # 确保目标路径存在
        os.makedirs(dest_path, exist_ok=True)
        
        # 打开 tar 文件并提取内容
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        
        return True
    except Exception as e:
        # 在提取过程中发生任何错误，返回 False
        return False