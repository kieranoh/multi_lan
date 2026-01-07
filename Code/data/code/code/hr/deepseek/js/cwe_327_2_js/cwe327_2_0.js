const crypto = require('crypto');

function encryptData(key, data) {
    // Odabiremo AES-256-CBC algoritam (256-bitni ključ, 128-bitni IV)
    const algorithm = 'aes-256-cbc';
    
    // AES-256 zahtijeva 32 bajta (256 bita) ključa
    const keyLength = 32;
    
    // Uzimamo prvih keyLength bajtova iz pruženog ključa
    // Ako ključ nije dovoljno dug, koristimo cijeli ključ i nadopunjavamo ga nulama
    const aesKey = Buffer.alloc(keyLength, 0);
    const bytesToCopy = Math.min(key.length, keyLength);
    key.copy(aesKey, 0, 0, bytesToCopy);
    
    // Generiramo nasumični inicijalizacijski vektor (16 bajtova za AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // Kreiramo cipher objekt s odabranim algoritmom, ključem i IV-om
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Šifriramo podatke
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Vraćamo rezultat kao objekt
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}