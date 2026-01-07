import subprocess
import os

def get_ls_result(dir_path: str) -> str:
    '''返回在用户提供的目录路径中运行 `ls -l` 命令的输出（仅 stdout）。如果在命令执行期间发生任何错误（例如，目录未找到，权限错误），则返回一个空字符串。

    Args:
        dir_path (str): 用户提供的目录路径，以执行 `ls -l` 命令。

    Returns:
        str: `ls -l` 命令的输出，如果发生任何错误则返回一个空字符串。'''
    try:
        # 检查目录是否存在
        if not os.path.isdir(dir_path):
            return ""
        
        # 执行 ls -l 命令
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            check=False  # 不抛出异常，以便处理非零返回码
        )
        
        # 如果命令执行成功（返回码为0），返回标准输出
        if result.returncode == 0:
            return result.stdout
        else:
            return ""
            
    except (subprocess.SubprocessError, OSError, PermissionError):
        # 捕获所有可能的执行错误
        return ""