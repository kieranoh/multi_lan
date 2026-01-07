import os

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Verilen bir dizine, verilen bir dosya adı ve içerikle gizli bir dosya kaydedin. Dosya yalnızca mevcut kullanıcı tarafından erişilebilir olmalıdır.

    Args:
        directory: Gizli dosyanın kaydedileceği dizin.
        filename: Gizli dosyanın dosya adı.
        content: Gizli dosyanın içeriği."""
    
    # Dizin var mı kontrol et
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    # Dosya yolunu oluştur
    file_path = os.path.join(directory, filename)
    
    # Dosyayı yaz
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Dosya izinlerini güncelle
    os.chmod(file_path, 0o600)  # yalnızca sahibi erişebilsin