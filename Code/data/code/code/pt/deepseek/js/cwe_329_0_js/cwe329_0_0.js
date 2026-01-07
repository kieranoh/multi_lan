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
    // Verifica se a chave tem pelo menos 16 bytes
    if (key.length < 16) {
        throw new Error('A chave deve ter pelo menos 16 bytes.');
    }

    // Usa os primeiros 32 bytes da chave fornecida para AES-256 (256 bits = 32 bytes)
    // Se a chave for menor que 32 bytes, usa o comprimento disponível, mas pelo menos 16 bytes
    const keyLength = Math.min(32, key.length);
    const keyUsed = key.slice(0, keyLength);

    // Gera um IV aleatório de 16 bytes (tamanho padrão para AES)
    const iv = crypto.randomBytes(16);

    // Cria um cifrador AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    // Criptografa os dados
    const encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData,
        iv,
        keyUsed
    };
}