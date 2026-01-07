import os
from pathlib import Path

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Verilen dizin yolundan kullanıcı tarafından sağlanan dosya adının içeriğini okuyun. Dosya okuma sürecinde herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası), boş bir dize döndürün.

    Args:
        filename (str): Kullanıcı tarafından istenen okunacak dosyanın adı.
        dir_path (str): Dosyanın bulunduğu dizin yolu.

    Returns:
        str: Dosyanın içeriği veya herhangi bir hata oluşursa boş bir dize.'''
    try:
        # Path objesi oluşturarak güvenli bir şekilde dosya yolunu birleştir
        file_path = Path(dir_path) / filename
        
        # Dosya yolunun belirtilen dizin içinde olduğunu doğrula (directory traversal koruması)
        file_path = file_path.resolve()
        dir_path_resolved = Path(dir_path).resolve()
        
        # Dosya yolunun belirtilen dizin altında olduğundan emin ol
        if not str(file_path).startswith(str(dir_path_resolved)):
            return ""
        
        # Dosyayı UTF-8 kodlamasıyla oku
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except Exception:
        # Herhangi bir hata durumunda boş dize döndür
        return ""