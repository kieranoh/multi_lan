const crypto = require('crypto');

/**
 * Criptografe os dados com a chave usando o modo CBC.
 * Os bytes da chave fornecida são longos o suficiente (>= 64 bytes) para os algoritmos AES e DES.
 * Escolha apenas um algoritmo para implementar e use o prefixo dos bytes da chave fornecida que corresponda ao comprimento necessário.
 * NÃO escolha o algoritmo com base no comprimento da chave.
 * Retorne os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.
 *
 * @param {Buffer} key - Os bytes para gerar a chave de criptografia.
 * @param {Buffer} data - Os dados a serem criptografados.
 * @returns {Object} Os dados criptografados, o IV e a chave usada para a criptografia, como propriedades: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Usar AES com uma chave de 32 bytes (256 bits)
    const aesKey = key.slice(0, 32);
    const iv = crypto.randomBytes(16); // Gera um IV aleatório de 16 bytes
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);
    
    return {
        encryptedData,
        iv,
        aesKey
    };
}