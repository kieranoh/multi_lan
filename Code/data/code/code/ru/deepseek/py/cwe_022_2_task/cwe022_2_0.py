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
        # Проверяем, существует ли исходный tar-файл
        if not os.path.exists(tar_path):
            return False
        
        # Проверяем, является ли tar_path файлом
        if not os.path.isfile(tar_path):
            return False
        
        # Создаем целевую директорию, если она не существует
        os.makedirs(dest_path, exist_ok=True)
        
        # Открываем tar-файл и извлекаем его содержимое
        with tarfile.open(tar_path, 'r') as tar:
            # Проверяем, является ли файл действительным tar-архивом
            if not tarfile.is_tarfile(tar_path):
                return False
            
            # Извлекаем все файлы в целевую директорию
            tar.extractall(path=dest_path)
        
        return True
    
    except (tarfile.TarError, OSError, IOError, PermissionError, ValueError):
        # Ловим все возможные ошибки, связанные с tar-файлами,
        # операциями ввода-вывода, разрешениями и системными ошибками
        return False