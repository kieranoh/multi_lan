const crypto = require('crypto');

/**
 * Datuak AES eta CBC moduan gakoa erabiliz enkriptatu.
 * Emandako gako byteak nahikoa luzeak dira (>= 64 byte). Erabili emandako gako byteen aurprefixa, beharrezko luzera bat datorrena.
 * Itzuli enkriptatutako datuak, IV (hasierako bideratzailea) eta enkriptatzeko erabilitako gakoa.
 *
 * @param {Buffer} key - Enkriptatzeko gakoa sortzeko byteak (gutxienez 16 byte).
 * @param {Buffer} data - Enkriptatu beharreko datuak.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa.
 */
function encrypt_data(key, data) {
    const iv = crypto.randomBytes(16);
    const cipher = crypto.createCipheriv('aes-256-cbc', key.slice(0, 32), iv);
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: key.slice(0, 32)
    };
}