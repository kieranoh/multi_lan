const crypto = require('crypto');

/**
 * Genera una clau privada DSA, exporta-la utilitzant el format PEM i retorna-la com una cadena.
 *
 * @returns {string} La clau privada DSA en format PEM.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;

    const { privateKey } = generateKeyPairSync('dsa', {
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