const crypto = require('crypto');

/**
 * Enkriptujte podatke sa ključem koristeći CBC mod.
 * Vratite enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.
 *
 * @param {Buffer} key - Bajtovi za generisanje ključa za enkripciju.
 * @param {Buffer} data - Podaci za enkripciju.
 * @returns {Object} Enkriptovani podaci, IV i ključ korišćen za enkripciju, kao svojstva: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Odabir AES algoritma i generisanje IV
    const algorithm = 'aes-256-cbc'; // Može se koristiti i 'aes-128-cbc'
    const iv = crypto.randomBytes(16); // AES blok veličina je 16 bajtova
    const aesKey = key.slice(0, 32); // Uzimanje prvih 32 bajta ključa za AES-256

    // Kreiranje enkriptor
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}