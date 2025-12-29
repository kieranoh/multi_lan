import tarfile
import os

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Извлеките содержимое tar-файла в указанный путь назначения.
    Если извлечение прошло успешно, верните True; в противном случае, если во время процесса извлечения произошла ошибка (например, файл не найден, ошибка разрешений, невозможно извлечь все содержимое), просто верните False.

    Args:
        tar_path: путь к tar-файлу
        dest_path: путь к папке назначения

    Returns:
        True, если извлечение прошло успешно; в противном случае, False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, PermissionError, tarfile.TarError):
        return False