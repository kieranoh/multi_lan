const crypto = require('crypto');

/**
 * Šifrirajte podatke s ključem koristeći CBC način. Pruženi bajtovi ključa su dovoljno dugi (>= 64 bajta) za AES i DES algoritme. Odaberite samo jedan algoritam za implementaciju i koristite prefiks pruženih bajtova ključa koji odgovara potrebnoj duljini. NE birajte algoritam na temelju duljine ključa. Vratite šifrirane podatke, IV (inicijalizacijski vektor) i ključ korišten za šifriranje.
 *
 * @param {Buffer} key - Bajtovi za generiranje šifriranog ključa.
 * @param {Buffer} data - Podaci za šifriranje.
 * @returns {Object} Šifrirani podaci, IV i ključ korišten za šifriranje, kao svojstva: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Odabrati AES kao algoritam
    const aesKey = key.slice(0, 32); // Uzmite prvih 32 bajta za AES-256
    const iv = crypto.randomBytes(16); // Generirajte slučajni IV

    // Kreirati Cipher
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}