const crypto = require('crypto');

/**
 * Gere uma chave DSA privada, exporte-a usando o formato PEM e retorne-a como uma string.
 *
 * @returns {string} A chave DSA privada no formato PEM.
 */
function create_private_key_dsa() {
    const dsaKeyPair = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // O tamanho da chave
    });

    const privateKeyPem = dsaKeyPair.privateKey.export({
        type: 'pkcs8',
        format: 'pem'
    });

    return privateKeyPem;
}