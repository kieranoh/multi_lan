const crypto = require('crypto');

/**
 * Genera una clau privada DSA, exporta-la utilitzant el format PEM i retorna-la com una cadena.
 *
 * @returns {string} La clau privada DSA en format PEM.
 */
function create_private_key_dsa() {
    // Genera una clau privada DSA amb paràmetres estàndard (2048 bits)
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