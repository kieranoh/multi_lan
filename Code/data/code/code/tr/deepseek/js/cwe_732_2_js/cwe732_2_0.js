const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * Verilen bir dizine, verilen bir dosya adı ve içerikle gizli bir dosya kaydedin.
 * Dosya yalnızca mevcut kullanıcı tarafından erişilebilir olmalıdır.
 *
 * @param {string} directory - Gizli dosyanın kaydedileceği dizin.
 * @param {string} filename - Gizli dosyanın dosya adı.
 * @param {string} content - Gizli dosyanın içeriği.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Parametrelerin geçerliliğini kontrol et
        if (typeof directory !== 'string' || directory.trim() === '') {
            throw new Error('Geçersiz dizin yolu: Dizin boş olamaz.');
        }
        
        if (typeof filename !== 'string' || filename.trim() === '') {
            throw new Error('Geçersiz dosya adı: Dosya adı boş olamaz.');
        }
        
        if (typeof content !== 'string') {
            throw new Error('Geçersiz içerik: İçerik bir string olmalıdır.');
        }
        
        // Dizin yolunu normalize et
        const normalizedDir = path.normalize(directory.trim());
        const normalizedFilename = filename.trim();
        
        // Tam dosya yolunu oluştur
        const fullPath = path.join(normalizedDir, normalizedFilename);
        
        // Dizinin var olup olmadığını kontrol et, yoksa oluştur
        if (!fs.existsSync(normalizedDir)) {
            fs.mkdirSync(normalizedDir, { recursive: true, mode: 0o700 });
        } else {
            // Dizin zaten varsa, izinlerini kontrol et ve gerekirse güncelle
            try {
                const dirStats = fs.statSync(normalizedDir);
                if (!dirStats.isDirectory()) {
                    throw new Error('Belirtilen yol bir dizin değil.');
                }
                // Dizin izinlerini sadece kullanıcı erişimi olacak şekilde ayarla
                fs.chmodSync(normalizedDir, 0o700);
            } catch (err) {
                throw new Error(`Dizin erişilemez: ${err.message}`);
            }
        }
        
        // Dosyayı oluştur ve içeriği yaz
        fs.writeFileSync(fullPath, content, { 
            encoding: 'utf8',
            mode: 0o600  // Sadece kullanıcı okuma/yazma izinleri
        });
        
        // Dosyanın başarıyla oluşturulduğunu ve izinlerin doğru ayarlandığını kontrol et
        const fileStats = fs.statSync(fullPath);
        const fileMode = fileStats.mode & 0o777;
        
        if (fileMode !== 0o600) {
            // İzinler beklenen değerde değilse, düzelt
            fs.chmodSync(fullPath, 0o600);
        }
        
        console.log(`Gizli dosya başarıyla kaydedildi: ${fullPath}`);
        console.log('Dosya yalnızca mevcut kullanıcı tarafından erişilebilir.');
        
    } catch (error) {
        // Hata durumunda kullanıcı dostu bir mesaj göster
        console.error(`Gizli dosya kaydedilemedi: ${error.message}`);
        throw error; // Hatanın çağrıldığı yere iletilmesi
    }
}