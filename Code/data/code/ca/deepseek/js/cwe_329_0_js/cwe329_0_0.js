const crypto = require('crypto');

function encrypt_data(key, data) {
    // Utilitzem AES-256-CBC, que requereix una clau de 32 bytes
    const keyLength = 32;
    // L'IV ha de ser de 16 bytes per a AES-CBC
    const ivLength = 16;
    
    // Assegurem que la clau sigui suficientment llarga
    if (key.length < keyLength) {
        throw new Error(`La clau ha de tenir almenys ${keyLength} bytes`);
    }
    
    // Utilitzem el prefix de la clau proporcionada de la longitud requerida
    const keyUsed = key.slice(0, keyLength);
    
    // Generem un IV aleatori
    const iv = crypto.randomBytes(ivLength);
    
    // Creem el cipher amb AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Xifrem les dades
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}