const crypto = require('crypto');

/**
 * Vygenerujte soukromý DSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.
 *
 * @returns {string} Soukromý DSA klíč ve formátu PEM.
 */
function create_private_key_dsa() {
    // Generování klíčového páru DSA s parametry 2048 bitů
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
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
}