const crypto = require('crypto');

/* * Özel bir DSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.
 *
 * @returns {string} PEM formatındaki DSA özel anahtarı. */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;
    
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // Anahtar boyutu
        privateKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        }
    });

    return privateKey;
}