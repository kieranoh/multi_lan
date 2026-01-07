const crypto = require('crypto');

/**
 * Verschlüsseln Sie die Daten mit dem Schlüssel unter Verwendung von AES und CBC-Modus.
 * Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes). Verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
 * Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.
 *
 * @param {Buffer} key - Die Bytes zur Generierung des Verschlüsselungsschlüssels (mindestens 16 Bytes).
 * @param {Buffer} data - Die zu verschlüsselnden Daten.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Die verschlüsselten Daten, der IV und der für die Verschlüsselung verwendete Schlüssel.
 */
function encrypt_data(key, data) {
    const keyLength = 32; // AES-256 benötigt einen 32-Byte Schlüssel
    const iv = crypto.randomBytes(16); // Initialisierungsvektor für CBC-Modus
    const encryptionKey = key.slice(0, keyLength); // Verwenden Sie das Präfix des Schlüssels

    const cipher = crypto.createCipheriv('aes-256-cbc', encryptionKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: Buffer.from(encryptedData, 'hex'),
        iv: iv,
        keyUsed: encryptionKey
    };
}