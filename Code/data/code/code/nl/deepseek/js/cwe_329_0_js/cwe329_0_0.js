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
    // Controleer of de sleutel minimaal 16 bytes bevat
    if (key.length < 16) {
        throw new Error('Key must be at least 16 bytes long');
    }

    // AES-256-CBC vereist een 32-byte sleutel (256 bits)
    const keyLength = 32;
    
    // Neem het voorvoegsel van de sleutelbytes met de vereiste lengte
    const keyUsed = key.slice(0, keyLength);
    
    // Genereer een willekeurige IV van 16 bytes (AES blokgrootte)
    const iv = crypto.randomBytes(16);
    
    // Maak een cipher object met AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Versleutel de gegevens
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