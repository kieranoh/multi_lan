const crypto = require('crypto');

function encryptData(key, data) {
    // Odlučujemo se za AES-256-CBC algoritam (fiksno, ne bazirano na dužini ključa)
    const algorithm = 'aes-256-cbc';
    
    // Za AES-256-CBC potreban nam je ključ od 32 bajta (256 bita)
    // Koristimo prvih 32 bajta od datog ključa
    const aesKey = key.slice(0, 32);
    
    // Generišemo nasumični IV (inicijalizacioni vektor) od 16 bajta za CBC mod
    const iv = crypto.randomBytes(16);
    
    // Kreiramo cipher objekat sa odabranim algoritmom, ključem i IV
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Enkriptujemo podatke
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Vraćamo rezultat kao objekat sa traženim svojstvima
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}