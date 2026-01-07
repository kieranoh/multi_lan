const crypto = require('crypto');

function encryptData(key, data) {
    // Zvolíme AES-256-CBC (32 bajtů klíč, 16 bajtů IV)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 256 bitů
    const ivLength = 16;  // 128 bitů
    
    // Zkontrolujeme, zda máme dostatek bajtů pro klíč a IV
    if (key.length < keyLength + ivLength) {
        throw new Error(`Klíč musí mít alespoň ${keyLength + ivLength} bajtů pro AES-256-CBC`);
    }
    
    // Vytvoříme šifrovací klíč z prvních keyLength bajtů
    const aesKey = key.slice(0, keyLength);
    
    // Vytvoříme IV z dalších ivLength bajtů
    const iv = key.slice(keyLength, keyLength + ivLength);
    
    // Vytvoříme šifrovací objekt
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Zašifrujeme data
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Vrátíme výsledek jako objekt
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}