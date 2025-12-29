const crypto = require('crypto');

/**
 * Zašifrujte data pomocí klíče pomocí AES a režimu CBC.
 * Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů). Použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce.
 * Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.
 *
 * @param {Buffer} key - Bajty pro generování šifrovacího klíče (alespoň 16 bajtů).
 * @param {Buffer} data - Data k zašifrování.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Zašifrovaná data, IV a klíč použitý pro šifrování.
 */
function encrypt_data(key, data) {
    const iv = crypto.randomBytes(16); // Vytvoření náhodného IV
    const keyUsed = key.slice(0, 32); // Užití prvních 32 bajtů klíče pro AES-256

    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: Buffer.from(encryptedData, 'hex'),
        iv: iv,
        keyUsed: keyUsed
    };
}