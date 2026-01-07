const crypto = require('crypto');

/**
 * Generiere einen privaten DSA-Schlüssel, exportiere ihn im PEM-Format und gebe ihn als String zurück.
 *
 * @returns {string} Der DSA-Private-Key im PEM-Format.
 */
function create_private_key_dsa() {
    // Generiere DSA-Schlüsselpaar mit 2048 Bit und Standard-Parameter (L=2048, N=256)
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
        divisorLength: 256,
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
}