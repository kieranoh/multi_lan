const crypto = require('crypto');

function encrypt_data(key, data) {
    // Gakoaren luzera egiaztatu (gutxienez 16 byte)
    if (key.length < 16) {
        throw new Error('Key must be at least 16 bytes long');
    }

    // AES-256-CBC erabili, beraz 32 byteko gakoa behar da
    // Emandako gakoaren lehen 32 byte erabili
    const keyLength = 32;
    const keyUsed = key.slice(0, keyLength);

    // Sortu ausazko IV (16 byte)
    const iv = crypto.randomBytes(16);

    // Sortu cipher objektua
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    // Enkriptatu datuak
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}