const crypto = require('crypto');

function encryptData(key, data) {
    // Välj AES-256-CBC som algoritm (enligt instruktionerna att välja en algoritm)
    const algorithm = 'aes-256-cbc';
    
    // För AES-256 behövs en 32-byte nyckel (256 bitar)
    // Använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden
    const aesKey = key.slice(0, 32);
    
    // Generera en slumpmässig IV (16 bytes för AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // Skapa cipher med AES-256-CBC
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Kryptera datan
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Returnera resultatet som ett objekt
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}