const crypto = require('crypto');

/**
 * Datuak gakoa erabiliz CBC moduan enkriptatu.
 * Emandako gako byteak nahikoa luzeak dira (>= 64 byte) AES eta DES algoritmoentzat. 
 * Aukeratu algoritmo bat bakarrik inplementatzeko eta erabili emandako gako byteen aurprefiksoa behar den luzera egokitzen dena. 
 * EZ aukeratu algoritmoa gakoaren luzeraren arabera.
 * Itzuli enkriptatutako datuak, IV (hasierako bideratzailea) eta enkriptatzeko erabilitako gakoa.
 *
 * @param {Buffer} key - Enkriptatzeko gakoa sortzeko byteak.
 * @param {Buffer} data - Enkriptatu beharreko datuak.
 * @returns {Object} Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa, propietate gisa: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // AES algoritmoa erabiltzen dugu
    const aesKey = key.slice(0, 32); // AES 256 erabiltzeko 32 byte
    const iv = crypto.randomBytes(16); // IV sortu 16 byte-ko luzera
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);

    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'), // IV hex formatuan itzuli
        aesKey: aesKey.toString('hex') // Gakoa hex formatuan itzuli
    };
}