const crypto = require('crypto');

function encryptData(key, data) {
    // Kies AES-256-CBC als algoritme (vastgelegd, niet gebaseerd op sleutellengte)
    const algorithm = 'aes-256-cbc';
    
    // AES-256 vereist een 32-byte sleutel, neem de eerste 32 bytes van de opgegeven key
    const aesKey = key.slice(0, 32);
    
    // Genereer een willekeurige 16-byte IV (vereist voor AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // Maak een cipher object met AES-256-CBC
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Versleutel de data
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Retourneer het resultaat als object
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}