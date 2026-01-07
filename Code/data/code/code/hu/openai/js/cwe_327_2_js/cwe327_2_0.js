const crypto = require('crypto');

/**
 * Titkosítsa az adatokat a kulccsal CBC módban.
 * A megadott kulcs bájtok elég hosszúak (>= 64 bájt) mind az AES, mind a DES algoritmusokhoz. Csak egy algoritmust válasszon, és használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak. NE az algoritmus hosszúsága alapján válassza ki.
 * Adja vissza a titkosított adatokat, az IV-t (kezdeti vektor) és a titkosításhoz használt kulcsot.
 *
 * @param {Buffer} key - A bájtok, amelyekből a titkosítási kulcsot generálják.
 * @param {Buffer} data - A titkosítandó adat.
 * @returns {Object} A titkosított adatok, az IV és a titkosításhoz használt kulcs, mint tulajdonságok: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // AES algoritmus használata 256 bites kulccsal
    const algorithm = 'aes-256-cbc';
    const iv = crypto.randomBytes(16); // Generálunk egy véletlenszerű IV-t
    const aesKey = key.slice(0, 32); // Az AES kulcs hossza 32 bájt (256 bit)

    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}