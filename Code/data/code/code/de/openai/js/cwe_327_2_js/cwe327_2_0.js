const crypto = require('crypto');

/**
 * Verschlüsseln Sie die Daten mit dem Schlüssel im CBC-Modus.
 * Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes) für sowohl AES- als auch DES-Algorithmen.
 * Wählen Sie nur einen Algorithmus zur Implementierung und verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
 * Wählen Sie den Algorithmus NICHT basierend auf der Länge des Schlüssels.
 * 
 * @param {Buffer} key - Die Bytes zur Generierung des Verschlüsselungsschlüssels.
 * @param {Buffer} data - Die zu verschlüsselnden Daten.
 * @returns {Object} Die verschlüsselten Daten, den IV und den für die Verschlüsselung verwendeten Schlüssel als Eigenschaften: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    const aesKey = key.slice(0, 32); // AES benötigt einen 256-Bit-Schlüssel (32 Bytes)
    const iv = crypto.randomBytes(16); // Generiere einen zufälligen IV
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv); // Erstelle einen AES-Cipher im CBC-Modus

    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]); // Verschlüssle die Daten

    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}