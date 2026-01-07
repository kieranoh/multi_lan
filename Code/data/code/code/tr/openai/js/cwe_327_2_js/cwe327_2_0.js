const crypto = require('crypto');

/**
 * Verileri CBC modunu kullanarak anahtar ile şifreleyin.
 * Verilen anahtar baytları, hem AES hem de DES algoritmaları için yeterince uzundur (>= 64 bayt).
 * Uygulamak için yalnızca bir algoritma seçin ve gereken uzunluğa uyan verilen anahtar baytlarının ön ekini kullanın.
 * Anahtarın uzunluğuna göre algoritmayı seçmeyin.
 * Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.
 *
 * @param {Buffer} key - Şifreleme anahtarını oluşturmak için baytlar.
 * @param {Buffer} data - Şifrelenecek veri.
 * @returns {Object} Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar, özellikler olarak: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // AES algoritmasını kullanacağız.
    const iv = crypto.randomBytes(16); // 16 baytlık bir IV oluştur
    const aesKey = key.slice(0, 32); // Anahtardan 32 baytlık bir kısım al

    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'base64');
    encryptedData += cipher.final('base64');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('base64'),
        aesKey: aesKey.toString('base64')
    };
}