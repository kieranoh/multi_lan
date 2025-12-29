const crypto = require('crypto');

function encrypt_data(key, data) {
    // Provera da li su ulazni podaci Buffer objekti
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('key i data moraju biti Buffer objekti');
    }

    // Provera minimalne dužine ključa
    if (key.length < 16) {
        throw new Error('key mora imati najmanje 16 bajtova');
    }

    // Koristimo prvih 32 bajta (256 bita) za AES-256-CBC
    const keyLength = 32;
    const keyUsed = key.slice(0, keyLength);

    // Generišemo nasumični IV (16 bajtova za AES-CBC)
    const iv = crypto.randomBytes(16);

    // Kreiramo cipher sa AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);

    // Enkriptujemo podatke
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());

    // Spajamo sve delove enkriptovanih podataka
    const encryptedData = Buffer.concat(encryptedChunks);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}