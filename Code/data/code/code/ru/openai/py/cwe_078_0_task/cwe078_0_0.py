import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Верните вывод (только stdout) команды `ls -l`, когда она выполняется в пользовательском каталоге. Если во время выполнения команды возникает ошибка (например, каталог не найден, ошибка доступа), верните пустую строку.

    Args:
        dir_path (str): Пользовательский каталог для выполнения команды `ls -l`.

    Returns:
        str: Вывод команды `ls -l`, или пустая строка, если произошла ошибка.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode == 0:
            return result.stdout
        else:
            return ''
    except Exception:
        return ''