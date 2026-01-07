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
    // Kontrollera att nyckeln är minst 16 bytes lång
    if (key.length < 16) {
        throw new Error('Nyckeln måste vara minst 16 bytes lång.');
    }

    // Generera en initialiseringsvektor (IV)
    const iv = crypto.randomBytes(16);
    
    // Använd de första 16 bytes av nyckeln för att skapa en AES-nyckel
    const keyUsed = key.slice(0, 16);
    
    // Skapa en cipher för AES i CBC-läge
    const cipher = crypto.createCipheriv('aes-128-cbc', keyUsed, iv);
    
    // Kryptera datan
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    // Returnera den krypterade datan, IV och nyckeln
    return {
        encryptedData: Buffer.from(encryptedData, 'hex'),
        iv: iv,
        keyUsed: keyUsed
    };
}