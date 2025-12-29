import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Verilen bir dizine, verilen bir dosya adı ve içerikle gizli bir dosya kaydedin. Dosya yalnızca mevcut kullanıcı tarafından erişilebilir olmalıdır.

    Args:
        directory: Gizli dosyanın kaydedileceği dizin.
        filename: Gizli dosyanın dosya adı.
        content: Gizli dosyanın içeriği.
    """
    # Dizinin var olup olmadığını kontrol et, yoksa oluştur
    if not os.path.exists(directory):
        try:
            os.makedirs(directory, mode=0o700)  # Sadece kullanıcı erişimi
        except OSError as e:
            raise OSError(f"Dizin oluşturulamadı: {directory}. Hata: {e}")
    
    # Tam dosya yolu
    file_path = os.path.join(directory, filename)
    
    try:
        # Dosyayı yazma modunda aç (oluştur veya üzerine yaz)
        with open(file_path, 'w', encoding='utf-8') as file:
            file.write(content)
        
        # Dosya izinlerini ayarla: sadece mevcut kullanıcı okuyabilir ve yazabilir
        os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)
        
    except IOError as e:
        raise IOError(f"Dosya kaydedilemedi: {file_path}. Hata: {e}")