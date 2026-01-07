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
    // Escolher AES-256-CBC como algoritmo (escolha fixa, independente do comprimento da chave)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 32 bytes para AES-256
    
    // Usar os primeiros 'keyLength' bytes da chave fornecida
    const aesKey = key.slice(0, keyLength);
    
    // Gerar um IV aleatório de 16 bytes (tamanho do bloco AES)
    const iv = crypto.randomBytes(16);
    
    // Criar cifrador
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Criptografar os dados
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Retornar o resultado como objeto
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}