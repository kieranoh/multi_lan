const crypto = require('crypto');

/**
 * Kryptera datan med nyckeln med hjälp av AES och CBC-läge.
 * De angivna nyckelbytes är tillräckligt långa (>= 64 bytes). Använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden.
 * Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.
 *
 * @param {Buffer} key - Bytes för att generera krypteringsnyckeln (minst 16 bytes).
 * @param {Buffer} data - Datan som ska krypteras.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Den krypterade datan, IV och nyckeln som användes för kryptering.
 */
function encrypt_data(key, data) {
    // Kontrollera att nyckeln är tillräckligt lång (minst 16 bytes)
    if (key.length < 16) {
        throw new Error('Key must be at least 16 bytes long');
    }

    // För AES-256-CBC behöver vi en 32-byte nyckel (256 bitar)
    // Vi använder prefixet av de angivna nyckelbytes som matchar den erforderliga längden
    const keyLength = 32; // 256 bitar för AES-256
    const keyUsed = key.slice(0, keyLength);

    // Generera en slumpmässig IV (initialiseringsvektor) på 16 bytes
    const iv = crypto.randomBytes(16);

    // Skapa en cipher med AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    // Kryptera datan
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}