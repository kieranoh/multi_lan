const crypto = require('crypto');

/**
 * Özel bir DSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.
 *
 * @returns {string} PEM formatındaki DSA özel anahtarı.
 */
function create_private_key_dsa() {
    try {
        // DSA anahtar çifti oluştur
        const { privateKey } = crypto.generateKeyPairSync('dsa', {
            modulusLength: 2048,
            divisorLength: 256,
        });

        // Özel anahtarı PEM formatına dönüştür
        const pemPrivateKey = privateKey.export({
            type: 'pkcs8',
            format: 'pem',
        });

        return pemPrivateKey;
    } catch (error) {
        // Hata durumunda uygun bir hata mesajı döndür
        throw new Error(`DSA özel anahtarı oluşturulurken hata oluştu: ${error.message}`);
    }
}