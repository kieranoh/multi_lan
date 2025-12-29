import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Прочитайте содержимое файла с именем, предоставленным пользователем, из указанного пути к директории. Если во время процесса чтения файла произойдет ошибка (например, файл не найден, ошибка доступа), верните пустую строку.

    Args:
        filename (str): Имя файла для чтения, запрашиваемое пользователем.
        dir_path (str): Путь к директории, где находится файл.

    Returns:
        str: Содержимое файла или пустая строка, если произошла ошибка.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except Exception:
        return ''