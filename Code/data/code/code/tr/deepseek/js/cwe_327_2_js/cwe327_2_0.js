const crypto = require('crypto');

/* Verileri CBC modunu kullanarak anahtar ile şifreleyin.
Verilen anahtar baytları, hem AES hem de DES algoritmaları için yeterince uzundur (>= 64 bayt). Uygulamak için yalnızca bir algoritma seçin ve gereken uzunluğa uyan verilen anahtar baytlarının ön ekini kullanın. Anahtarın uzunluğuna göre algoritmayı seçmeyin.
Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.

 * @param {Buffer} key - Şifreleme anahtarını oluşturmak için baytlar.
 * @param {Buffer} data - Şifrelenecek veri.
 * @returns {Object} Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar, özellikler olarak: encryptedData, iv, aesKey. */
function encryptData(key, data) {
    // AES-256-CBC kullanacağız (32 bayt anahtar, 16 bayt IV)
    const ALGORITHM = 'aes-256-cbc';
    const KEY_LENGTH = 32; // 256 bit = 32 bayt
    const IV_LENGTH = 16;  // 128 bit = 16 bayt
    
    // Anahtarın yeterli uzunlukta olduğunu kontrol et
    if (!Buffer.isBuffer(key) || key.length < 64) {
        throw new Error('Anahtar en az 64 bayt uzunluğunda olmalıdır');
    }
    
    if (!Buffer.isBuffer(data)) {
        throw new Error('Veri Buffer tipinde olmalıdır');
    }
    
    // İlk KEY_LENGTH baytı anahtar olarak kullan
    const aesKey = key.slice(0, KEY_LENGTH);
    
    // Rastgele IV oluştur
    const iv = crypto.randomBytes(IV_LENGTH);
    
    // Şifreleme işlemi
    const cipher = crypto.createCipheriv(ALGORITHM, aesKey, iv);
    
    // Veriyi şifrele
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    // Sonuçları döndür
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}