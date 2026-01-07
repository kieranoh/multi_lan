import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Сохраните секретный файл в указанной директории с заданным именем файла и содержимым. Файл должен быть доступен только текущему пользователю.

    Args:
        directory: Директория для сохранения секретного файла.
        filename: Имя файла секретного файла.
        content: Содержимое секретного файла."""
    
    # Создаем директорию, если она не существует
    if not os.path.exists(directory):
        try:
            os.makedirs(directory, mode=0o700)  # Создаем с правами только для владельца
        except OSError as e:
            raise OSError(f"Не удалось создать директорию '{directory}': {e}")
    
    # Проверяем, что директория существует и является директорией
    if not os.path.isdir(directory):
        raise ValueError(f"'{directory}' не является директорией или не существует")
    
    # Полный путь к файлу
    filepath = os.path.join(directory, filename)
    
    try:
        # Записываем содержимое в файл
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        
        # Устанавливаем права доступа только для текущего пользователя
        # 0o600: владелец может читать и писать, группа и другие не имеют доступа
        os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)
        
    except IOError as e:
        raise IOError(f"Не удалось записать файл '{filepath}': {e}")
    except OSError as e:
        raise OSError(f"Не удалось установить права доступа для файла '{filepath}': {e}")