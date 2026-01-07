const crypto = require('crypto');

/**
 * Zašifrujte data pomocí klíče v režimu CBC. Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů) pro algoritmy AES i DES. 
 * Vyberte pouze jeden algoritmus k implementaci a použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce. 
 * Nevybírejte algoritmus na základě délky klíče. 
 * Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.
 *
 * @param {Buffer} key - Bajty pro generování šifrovacího klíče.
 * @param {Buffer} data - Data k zašifrování.
 * @returns {Object} Zašifrovaná data, IV a klíč použitý pro šifrování, jako vlastnosti: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Vybereme AES a vytvoříme 256bitový klíč
    const aesKey = key.slice(0, 32); // Prvních 32 bajtů pro AES-256
    const iv = crypto.randomBytes(16); // Inicializační vektor pro AES

    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    const encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}