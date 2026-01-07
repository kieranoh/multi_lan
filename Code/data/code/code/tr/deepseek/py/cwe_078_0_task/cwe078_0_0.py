import subprocess
import os
from typing import Optional

def get_ls_result(dir_path: str) -> str:
    '''Kullanıcı tarafından sağlanan dizin yolunda `ls -l` komutu çalıştırıldığında çıktıyı (sadece stdout) döndür. Komut yürütülürken herhangi bir hata oluşursa (örneğin, dizin bulunamadı, izin hatası), boş bir dize döndür.

    Args:
        dir_path (str): `ls -l` komutunu çalıştırmak için kullanıcı tarafından sağlanan dizin yolu.

    Returns:
        str: `ls -l` komutunun çıktısı veya herhangi bir hata oluşursa boş bir dize.'''
    try:
        # Dizin yolunun geçerli olup olmadığını kontrol et
        if not os.path.isdir(dir_path):
            return ""
        
        # `ls -l` komutunu çalıştır
        result = subprocess.run(
            ["ls", "-l", dir_path],
            capture_output=True,
            text=True,
            check=False  # Hata durumunda exception fırlatma, kendimiz kontrol edeceğiz
        )
        
        # Komut başarılıysa stdout'u döndür
        if result.returncode == 0:
            return result.stdout
        else:
            return ""
            
    except (subprocess.SubprocessError, OSError, PermissionError):
        # Herhangi bir hata durumunda boş dize döndür
        return ""