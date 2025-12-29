const crypto = require('crypto');

function encryptData(key, data) {
    // Valitaan AES-256-CBC algoritmi (avaimen pituus 256 bittiä = 32 tavua)
    // Käytetään avaimen ensimmäisiä 32 tavua AES-avaimena
    const aesKey = key.slice(0, 32);
    
    // Luodaan satunnainen 16-tavuinen IV (Initialization Vector) CBC-tilaa varten
    const iv = crypto.randomBytes(16);
    
    // Luodaan salain AES-256-CBC-tilassa
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // Salataan data
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Palautetaan tulos objektina
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}