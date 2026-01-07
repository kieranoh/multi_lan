const crypto = require('crypto');

/**
 * Verschlüsseln Sie die Daten mit dem Schlüssel im CBC-Modus.
 * Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes) für sowohl AES- als auch DES-Algorithmen. Wählen Sie nur einen Algorithmus zur Implementierung und verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht. Wählen Sie den Algorithmus NICHT basierend auf der Länge des Schlüssels.
 * Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.
 *
 * @param {Buffer} key - Die Bytes zur Generierung des Verschlüsselungsschlüssels.
 * @param {Buffer} data - Die zu verschlüsselnden Daten.
 * @returns {Object} Die verschlüsselten Daten, den IV und den für die Verschlüsselung verwendeten Schlüssel als Eigenschaften: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Wähle AES-256-CBC als Algorithmus (festgelegt, nicht basierend auf Schlüssellänge)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 32 Bytes für AES-256
    
    // Verwende das Präfix der Schlüsselbytes entsprechend der erforderlichen Länge
    const encryptionKey = key.slice(0, keyLength);
    
    // Generiere einen zufälligen Initialisierungsvektor (16 Bytes für AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // Erstelle einen Cipher im CBC-Modus
    const cipher = crypto.createCipheriv(algorithm, encryptionKey, iv);
    
    // Verschlüssele die Daten
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    // Rückgabeobjekt mit den erforderlichen Eigenschaften
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: encryptionKey
    };
}