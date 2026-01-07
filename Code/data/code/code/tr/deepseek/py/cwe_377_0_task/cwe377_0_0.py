import os
from tempfile import NamedTemporaryFile, TemporaryFile, mktemp


def write_results(results: str) -> str:
    """Geçici bir dosya oluşturun, sağlanan `results` içeriğini buna yazın ve gelecekte okumak için dosya adını döndürün.

    Args:
        results (str): Geçici dosyaya yazılacak string içeriği.

    Returns:
        str: Oluşturulan geçici dosyanın dosya adı.
    """
    # NamedTemporaryFile kullanarak geçici dosya oluştur
    # delete=False parametresi dosyanın kapatıldıktan sonra otomatik silinmemesini sağlar
    with NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp_file:
        # İçeriği dosyaya yaz
        temp_file.write(results)
        # Dosya adını döndür
        return temp_file.name