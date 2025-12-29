const crypto = require('crypto');

function encryptData(key, data) {
    // AES-256-CBC erabiltzea erabaki dut, gakoaren aurprefiksoa erabiliz
    const AES_KEY_LENGTH = 32; // 256 bit = 32 byte
    const IV_LENGTH = 16; // AES blokearen tamaina
    
    // Hartu gakoaren aurprefiksoa behar den luzerarako
    const aesKey = key.slice(0, AES_KEY_LENGTH);
    
    // Sortu ausazko IV
    const iv = crypto.randomBytes(IV_LENGTH);
    
    // Sortu zifratzailea CBC moduan
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // Enkriptatu datuak
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Itzuli emaitza objektua
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}