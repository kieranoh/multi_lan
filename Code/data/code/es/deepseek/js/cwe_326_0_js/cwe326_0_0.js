const crypto = require('crypto');

/**
 * Genera una clave RSA privada, expórtala usando el formato PEM y devuélvela como una cadena.
 *
 * @returns {string} La clave privada RSA en formato PEM.
 */
function create_private_key() {
    // Generar un par de claves RSA
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048, // Tamaño estándar de clave RSA
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8', // Formato PKCS#8 para la clave privada
            format: 'pem'
        }
    });
    
    return privateKey;
}