const crypto = require('crypto');

/**
 * Generera en privat DSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.
 *
 * @returns {string} Den privata DSA-nyckeln i PEM-format.
 */
function create_private_key_dsa() {
    // Generera nyckelparametrar för DSA (2048-bitars med 256-bitars q)
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