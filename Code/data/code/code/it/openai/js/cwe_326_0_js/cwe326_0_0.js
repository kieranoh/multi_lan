const { generateKeyPairSync } = require('crypto');

/**
 * Genera una chiave RSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
 *
 * @returns {string} La chiave privata RSA in formato PEM.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });
    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}