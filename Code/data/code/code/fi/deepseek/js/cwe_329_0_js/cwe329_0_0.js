const crypto = require('crypto');

function encrypt_data(key, data) {
    // Varmistetaan, että avain on vähintään 16 tavua
    if (key.length < 16) {
        throw new Error('Avaimen on oltava vähintään 16 tavua');
    }

    // Käytetään avaimen etuliidettä (ensimmäiset 32 tavua) AES-256-CBC:lle
    // AES-256 vaatii 32 tavun (256 bitin) avaimen
    const keyUsed = key.slice(0, 32);
    
    // Luodaan satunnainen 16 tavun IV (Initialization Vector)
    const iv = crypto.randomBytes(16);
    
    // Luodaan salain AES-256-CBC-tilassa
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Salaa tiedot
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}