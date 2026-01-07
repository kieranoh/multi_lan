import os
import subprocess
import sys

def get_ls_result(dir_path: str) -> str:
    '''Верните вывод (только stdout) команды `ls -l`, когда она выполняется в пользовательском каталоге. Если во время выполнения команды возникает ошибка (например, каталог не найден, ошибка доступа), верните пустую строку.

    Args:
        dir_path (str): Пользовательский каталог для выполнения команды `ls -l`.

    Returns:
        str: Вывод команды `ls -l`, или пустая строка, если произошла ошибка.'''
    try:
        # Проверяем, существует ли каталог
        if not os.path.isdir(dir_path):
            return ""
        
        # Выполняем команду ls -l в указанном каталоге
        result = subprocess.run(
            ['ls', '-l', dir_path],
            capture_output=True,
            text=True,
            cwd=dir_path if os.path.isdir(dir_path) else None
        )
        
        # Возвращаем только stdout, если команда выполнена успешно
        if result.returncode == 0:
            return result.stdout
        else:
            return ""
            
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Ловим все возможные ошибки выполнения команды или доступа
        return ""