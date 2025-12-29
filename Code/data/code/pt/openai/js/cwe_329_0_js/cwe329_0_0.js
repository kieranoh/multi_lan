const crypto = require('crypto');

/**
 * Criptografe os dados com a chave usando AES e modo CBC.
 * Os bytes da chave fornecida são longos o suficiente (>= 64 bytes). Use o prefixo dos bytes da chave fornecida que corresponde ao comprimento necessário.
 * Retorne os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.
 *
 * @param {Buffer} key - Os bytes para gerar a chave de criptografia (pelo menos 16 bytes).
 * @param {Buffer} data - Os dados a serem criptografados.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Os dados criptografados, o IV e a chave usada para a criptografia.
 */
function encrypt_data(key, data) {
    // Garante que a chave tenha pelo menos 16 bytes
    const keyUsed = key.slice(0, 32); // AES-256
    const iv = crypto.randomBytes(16); // Gera um IV aleatório de 16 bytes

    // Cria o cipher usando o algoritmo AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    // Criptografa os dados
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}