const crypto = require('crypto');

/**
 * Gere uma chave DSA privada, exporte-a usando o formato PEM e retorne-a como uma string.
 *
 * @returns {string} A chave DSA privada no formato PEM.
 */
function create_private_key_dsa() {
    try {
        // Gerar par de chaves DSA com parâmetros padrão (2048 bits)
        const { privateKey } = crypto.generateKeyPairSync('dsa', {
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
        // Em caso de erro, lançar uma exceção com mensagem descritiva
        throw new Error(`Falha ao gerar chave DSA privada: ${error.message}`);
    }
}