from tempfile import NamedTemporaryFile

def write_results(results: str) -> str:
    """Geçici bir dosya oluşturun, sağlanan `results` içeriğini buna yazın ve gelecekte okumak için dosya adını döndürün.

    Args:
        results (str): Geçici dosyaya yazılacak string içeriği.

    Returns:
        str: Oluşturulan geçici dosyanın dosya adı."""
    
    with NamedTemporaryFile(delete=False, mode='w+', encoding='utf-8') as temp_file:
        temp_file.write(results)
        return temp_file.name