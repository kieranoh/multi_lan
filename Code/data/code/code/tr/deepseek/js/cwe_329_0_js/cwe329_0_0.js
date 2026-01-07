const crypto = require('crypto');

/**
 * Verileri AES ve CBC modunu kullanarak anahtar ile şifreleyin.
 * Sağlanan anahtar baytları yeterince uzundur (>= 64 bayt). Gerekli uzunluğa uyan sağlanan anahtar baytlarının ön ekini kullanın.
 * Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.
 *
 * @param {Buffer} key - Şifreleme anahtarını oluşturmak için baytlar (en az 16 bayt).
 * @param {Buffer} data - Şifrelenecek veri.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar.
 */
function encrypt_data(key, data) {
    // Anahtar uzunluğunu kontrol et (AES-256 için 32 bayt gereklidir)
    if (key.length < 16) {
        throw new Error('Anahtar en az 16 bayt uzunluğunda olmalıdır');
    }
    
    // AES-256-CBC için 32 bayt (256 bit) anahtar kullanacağız
    const KEY_LENGTH = 32;
    
    // Anahtar uzunluğu yeterliyse, ilk KEY_LENGTH baytını kullan
    // Aksi takdirde, mevcut anahtarı kullan ve geri kalanını doldur
    let keyUsed;
    if (key.length >= KEY_LENGTH) {
        keyUsed = key.slice(0, KEY_LENGTH);
    } else {
        // Anahtar yeterince uzun değilse, mevcut anahtarı kullan ve kalanını sıfırlarla doldur
        keyUsed = Buffer.alloc(KEY_LENGTH);
        key.copy(keyUsed, 0, 0, key.length);
        // Kalan kısmı sıfırlarla doldur
        keyUsed.fill(0, key.length);
    }
    
    // Rastgele bir IV (Initialization Vector) oluştur (AES-CBC için 16 bayt)
    const iv = crypto.randomBytes(16);
    
    // AES-256-CBC şifreleyici oluştur
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Veriyi şifrele
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    // Şifrelenmiş veriyi birleştir
    const encryptedData = Buffer.concat(encryptedChunks);
    
    // Sonucu döndür
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}