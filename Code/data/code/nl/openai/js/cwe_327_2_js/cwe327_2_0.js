const crypto = require('crypto');

/**
 * Versleutel de gegevens met de sleutel met behulp van de CBC-modus.
 * De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes) voor zowel AES- als DES-algoritmen. 
 * Kies slechts één algoritme om te implementeren en gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte. 
 * Kies het algoritme NIET op basis van de lengte van de sleutel.
 * Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.
 *
 * @param {Buffer} key - De bytes om de versleutelingssleutel te genereren.
 * @param {Buffer} data - De te versleutelen gegevens.
 * @returns {Object} De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt, als eigenschappen: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    const iv = crypto.randomBytes(16); // AES IV moet 16 bytes zijn
    const aesKey = key.slice(0, 32); // Gebruik de eerste 32 bytes voor AES-256
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);

    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}