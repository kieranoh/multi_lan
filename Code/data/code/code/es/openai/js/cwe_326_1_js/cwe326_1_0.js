const crypto = require('crypto');

/**
 * Generar una clave DSA privada, exportarla usando el formato PEM y devolverla como una cadena.
 *
 * @returns {string} La clave DSA privada en formato PEM.
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