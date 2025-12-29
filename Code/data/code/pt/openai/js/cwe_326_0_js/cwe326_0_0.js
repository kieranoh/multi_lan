const { generateKeyPairSync } = require('crypto');

/**
 * Gere uma chave RSA privada, exporte-a usando o formato PEM e retorne-a como uma string.
 *
 * @returns {string} A chave privada RSA no formato PEM. 
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}