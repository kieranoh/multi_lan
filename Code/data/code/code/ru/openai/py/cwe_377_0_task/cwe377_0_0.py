from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Создайте временный файл, запишите в него предоставленные `results` и верните имя файла для дальнейшего чтения.

    Args:
        results (str): Содержимое строки для записи во временный файл.

    Returns:
        str: Имя созданного временного файла."""
    
    with NamedTemporaryFile(delete=False, mode='w+', encoding='utf-8') as temp_file:
        temp_file.write(results)
        return temp_file.name