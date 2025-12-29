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
    // Überprüfen, ob der Schlüssel mindestens 16 Bytes lang ist
    if (key.length < 16) {
        throw new Error('Der Schlüssel muss mindestens 16 Bytes lang sein.');
    }

    // AES-256-CBC benötigt einen 32-Byte-Schlüssel (256 Bit)
    const keyLength = 32;
    
    // Verwenden Sie das Präfix der Schlüsselbytes mit der erforderlichen Länge
    const keyUsed = key.slice(0, keyLength);
    
    // Generieren Sie einen zufälligen 16-Byte-IV für CBC-Modus
    const iv = crypto.randomBytes(16);
    
    // Erstellen Sie einen Cipher mit AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Verschlüsseln Sie die Daten
    const encryptedData = Buffer.concat([
        cipher.update(data),
        cipher.final()
    ]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}