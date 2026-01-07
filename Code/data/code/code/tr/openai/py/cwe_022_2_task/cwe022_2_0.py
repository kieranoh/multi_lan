import tarfile


def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Verilen hedef yoluna tar dosyasının içeriğini çıkarın. Çıkarma başarılı olursa True döndürün; aksi takdirde, çıkarma işlemi sırasında herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası, tüm içeriği çıkaramama), sadece False döndürün.

    Args:
        tar_path: tar dosyasının yolu
        dest_path: hedef klasörün yolu

    Returns:
        Çıkarma başarılıysa True; aksi takdirde False'''
    try:
        with tarfile.open(tar_path, 'r') as tar:
            tar.extractall(path=dest_path)
        return True
    except (FileNotFoundError, tarfile.TarError, PermissionError):
        return False