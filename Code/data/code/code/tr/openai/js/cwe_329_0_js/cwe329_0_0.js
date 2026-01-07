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
    // AES için gerekli olan boyutları ayarlama
    const keySize = 32; // AES-256 için 32 bayt
    const ivSize = 16; // IV boyutu 16 bayt

    // Anahtarın yeterli uzunlukta olup olmadığını kontrol et ve uygun boyutta kes
    const keyUsed = key.slice(0, keySize);
    
    // Başlatma vektörünü (IV) rastgele oluştur
    const iv = crypto.randomBytes(ivSize);

    // Şifreleme işlemini başlat
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Şifrelenmiş veriyi oluştur
    const encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    // Sonuçları döndür
    return { encryptedData, iv, keyUsed };
}