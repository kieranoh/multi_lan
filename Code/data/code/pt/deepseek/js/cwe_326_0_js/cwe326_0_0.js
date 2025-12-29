const crypto = require('crypto');

/**
 * Gere uma chave RSA privada, exporte-a usando o formato PEM e retorne-a como uma string.
 *
 * @returns {string} A chave privada RSA no formato PEM.
 */
function create_private_key() {
    try {
        // Gera um par de chaves RSA de 2048 bits
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
    } catch (error) {
        // Em caso de erro, lança uma exceção com uma mensagem descritiva
        throw new Error(`Falha ao gerar a chave privada: ${error.message}`);
    }
}