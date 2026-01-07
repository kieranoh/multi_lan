const crypto = require('crypto');

/**
 * Genera una chiave DSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
 *
 * @returns {string} La chiave DSA privata in formato PEM.
 */
function create_private_key_dsa() {
    // Genera una coppia di chiavi DSA
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // Lunghezza del modulo
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });

    // Restituisci la chiave privata in formato PEM
    return privateKey;
}