import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Создайте временный файл, запишите в него предоставленные `results` и верните имя файла для дальнейшего чтения.

    Args:
        results (str): Содержимое строки для записи во временный файл.

    Returns:
        str: Имя созданного временного файла.
    """
    # Создаем временный файл с режимом записи и чтения текста
    # delete=False гарантирует, что файл не будет автоматически удален при закрытии
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # Записываем содержимое results в файл
        temp_file.write(results)
        # Получаем имя файла
        filename = temp_file.name
    
    return filename