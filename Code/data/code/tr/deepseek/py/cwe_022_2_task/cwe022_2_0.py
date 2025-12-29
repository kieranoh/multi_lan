import tarfile
import os
from pathlib import Path

def extract_tar_to_path(tar_path, dest_path) -> bool:
    '''Verilen hedef yoluna tar dosyasının içeriğini çıkarın. Çıkarma başarılı olursa True döndürün; aksi takdirde, çıkarma işlemi sırasında herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası, tüm içeriği çıkaramama), sadece False döndürün.

    Args:
        tar_path: tar dosyasının yolu
        dest_path: hedef klasörün yolu

    Returns:
        Çıkarma başarılıysa True; aksi takdirde False'''
    try:
        # Giriş parametrelerini kontrol et
        if not tar_path or not dest_path:
            return False
        
        # Dosya varlığını kontrol et
        if not os.path.exists(tar_path):
            return False
        
        # Hedef dizini oluştur (eğer yoksa)
        dest_path_obj = Path(dest_path)
        dest_path_obj.mkdir(parents=True, exist_ok=True)
        
        # Tar dosyasını aç ve içeriği çıkar
        with tarfile.open(tar_path, 'r') as tar:
            # Güvenlik kontrolü: Dosyaların hedef dizin dışına çıkarılmamasını sağla
            for member in tar.getmembers():
                member_path = Path(member.name)
                # Mutlak yolları ve dizin traversal saldırılarını önle
                if member_path.is_absolute() or '..' in member_path.parts:
                    return False
            
            # Tüm dosyaları çıkar
            tar.extractall(path=dest_path)
        
        return True
        
    except (tarfile.TarError, OSError, IOError, PermissionError, ValueError):
        # Tüm olası hataları yakala ve False döndür
        return False
    except Exception:
        # Diğer beklenmeyen hatalar için de False döndür
        return False