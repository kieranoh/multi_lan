const crypto = require('crypto');

/**
 * Versleutel de gegevens met de sleutel met behulp van AES en CBC-modus.
 * De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes). Gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte.
 * Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.
 *
 * @param {Buffer} key - De bytes om de versleutelingssleutel te genereren (minimaal 16 bytes).
 * @param {Buffer} data - De te versleutelen gegevens.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt.
 */
function encrypt_data(key, data) {
    if (key.length < 16) {
        throw new Error('Key must be at least 16 bytes long.');
    }

    // Gebruik de eerste 16 bytes van de sleutel
    const keyUsed = key.slice(0, 16);
    const iv = crypto.randomBytes(16); // Genereer een random IV

    const cipher = crypto.createCipheriv('aes-128-cbc', keyUsed, iv);
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}