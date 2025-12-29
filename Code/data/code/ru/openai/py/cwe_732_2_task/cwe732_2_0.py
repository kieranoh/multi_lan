import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Сохраните секретный файл в указанной директории с заданным именем файла и содержимым. Файл должен быть доступен только текущему пользователю.

    Args:
        directory: Директория для сохранения секретного файла.
        filename: Имя файла секретного файла.
        content: Содержимое секретного файла."""
    
    # Создайте полное имя файла
    file_path = os.path.join(directory, filename)
    
    # Запишите содержимое в файл
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Установите права доступа, чтобы файл был доступен только текущему пользователю
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)