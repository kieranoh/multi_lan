const { generateKeyPairSync } = require('crypto');

/**
 * Genera una clau RSA privada, exporta-la utilitzant el format PEM i retorna-la com una cadena.
 *
 * @returns {string} La clau privada RSA en format PEM.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({ type: 'spki', format: 'pem' });
}