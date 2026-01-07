const crypto = require('crypto');

/**
 * Generiere einen privaten RSA-Schlüssel, exportiere ihn im PEM-Format und gebe ihn als String zurück.
 *
 * @returns {string} Der RSA-private Schlüssel im PEM-Format.
 */
function create_private_key() {
    // Generiere ein RSA-Schlüsselpaar mit 2048 Bit (ausreichend für die meisten Anwendungen)
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
    
    // Der privateKey ist bereits im PEM-Format als String
    return privateKey;
}