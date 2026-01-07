const { generateKeyPairSync } = require('crypto');

/**
 * Genera una clave RSA privada, expórtala usando el formato PEM y devuélvela como una cadena.
 *
 * @returns {string} La clave privada RSA en formato PEM.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048, // Longitud de la clave
    });

    // Exportar la clave privada en formato PEM
    const privateKeyPem = privateKey.export({
        type: 'pkcs1',
        format: 'pem',
    });

    return privateKeyPem;
}