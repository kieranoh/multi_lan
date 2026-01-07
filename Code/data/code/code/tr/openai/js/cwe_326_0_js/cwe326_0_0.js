const { generateKeyPairSync } = require('crypto');

/* * Özel bir RSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.
 *
 * @returns {string} PEM formatındaki RSA özel anahtarı. */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });
    return privateKey.export({ type: 'spki', format: 'pem' });
}