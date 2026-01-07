const crypto = require('crypto');

/* * Genera una clau RSA privada, exporta-la utilitzant el format PEM i retorna-la com una cadena.
 *
 * @returns {string} La clau privada RSA en format PEM. */
function create_private_key() {
    // Genera un parell de claus RSA de 2048 bits
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
    
    return privateKey;
}