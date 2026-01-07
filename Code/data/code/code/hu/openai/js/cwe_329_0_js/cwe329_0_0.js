const crypto = require('crypto');

/**
 * Titkosítsa az adatokat a kulccsal AES és CBC módban.
 * A megadott kulcs bájtok elég hosszúak (>= 64 bájt). Használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak.
 * Térjen vissza a titkosított adatokkal, az IV-vel (kezdeti vektor) és a titkosításhoz használt kulccsal.
 *
 * @param {Buffer} key - A titkosítási kulcs generálásához szükséges bájtok (legalább 16 bájt).
 * @param {Buffer} data - A titkosítandó adatok.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} A titkosított adatok, az IV és a titkosításhoz használt kulcs.
 */
function encrypt_data(key, data) {
    const iv = crypto.randomBytes(16);
    const keyUsed = key.slice(0, 32); // AES-256-hoz 32 bájtos kulcs szükséges
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}