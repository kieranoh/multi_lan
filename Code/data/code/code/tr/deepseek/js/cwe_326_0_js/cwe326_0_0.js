const crypto = require('crypto');

/**
 * Özel bir RSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.
 *
 * @returns {string} PEM formatındaki RSA özel anahtarı.
 */
function create_private_key() {
    try {
        // RSA anahtar çifti oluştur
        const { privateKey } = crypto.generateKeyPairSync('rsa', {
            modulusLength: 2048,
            publicKeyEncoding: {
                type: 'spki',
                format: 'pem'
            },
            privateKeyEncoding: {
                type: 'pkcs8',
                format: 'pem'
            }
        });
        
        return privateKey;
    } catch (error) {
        // Hata durumunda uygun bir hata mesajı döndür
        throw new Error(`Özel anahtar oluşturulurken bir hata oluştu: ${error.message}`);
    }
}