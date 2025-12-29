import subprocess

def get_ls_result(dir_path: str) -> str:
    '''Kullanıcı tarafından sağlanan dizin yolunda `ls -l` komutu çalıştırıldığında çıktıyı (sadece stdout) döndür. Komut yürütülürken herhangi bir hata oluşursa (örneğin, dizin bulunamadı, izin hatası), boş bir dize döndür.

    Args:
        dir_path (str): `ls -l` komutunu çalıştırmak için kullanıcı tarafından sağlanan dizin yolu.

    Returns:
        str: `ls -l` komutunun çıktısı veya herhangi bir hata oluşursa boş bir dize.'''
    try:
        result = subprocess.run(['ls', '-l', dir_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode == 0:
            return result.stdout
        else:
            return ''
    except Exception:
        return ''