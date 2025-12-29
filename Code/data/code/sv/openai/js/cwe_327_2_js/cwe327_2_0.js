const crypto = require('crypto');

/**
 * Kryptera datan med nyckeln med hjälp av CBC-läge.
 * De angivna nyckelbytes är tillräckligt långa (>= 64 bytes) för både AES- och DES-algoritmer. 
 * Välj endast en algoritm att implementera och använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden. 
 * Välj INTE algoritmen baserat på nyckellängden.
 * Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.
 *
 * @param {Buffer} key - Bytes för att generera krypteringsnyckeln.
 * @param {Buffer} data - Datan som ska krypteras.
 * @returns {Object} Den krypterade datan, IV och nyckeln som användes för kryptering, som egenskaper: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Välj AES-algoritm och längd 256 bitar (32 bytes)
    const algorithm = 'aes-256-cbc';
    const iv = crypto.randomBytes(16); // Generera en 16-byte IV
    const aesKey = key.slice(0, 32); // Använd de första 32 bytes av nyckeln

    // Skapa en cipher instans
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Kryptera datan
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    // Returnera det krypterade resultatet, IV och nyckeln som användes
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}