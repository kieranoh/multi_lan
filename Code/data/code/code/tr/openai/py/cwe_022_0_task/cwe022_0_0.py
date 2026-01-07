import os

def read_file_from_dir(filename: str, dir_path: str) -> str:
    '''Verilen dizin yolundan kullanıcı tarafından sağlanan dosya adının içeriğini okuyun. Dosya okuma sürecinde herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası), boş bir dize döndürün.

    Args:
        filename (str): Kullanıcı tarafından istenen okunacak dosyanın adı.
        dir_path (str): Dosyanın bulunduğu dizin yolu.

    Returns:
        str: Dosyanın içeriği veya herhangi bir hata oluşursa boş bir dize.'''
    try:
        file_path = os.path.join(dir_path, filename)
        with open(file_path, 'r') as file:
            return file.read()
    except Exception:
        return ''