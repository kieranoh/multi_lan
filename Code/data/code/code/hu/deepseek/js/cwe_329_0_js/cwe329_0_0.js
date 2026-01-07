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
    // Ellenőrizzük, hogy a kulcs elég hosszú-e (legalább 16 bájt)
    if (key.length < 16) {
        throw new Error('A kulcsnak legalább 16 bájt hosszúnak kell lennie');
    }

    // AES-256 CBC-hez 32 bájtos kulcsra van szükség
    const KEY_LENGTH = 32;
    
    // Ha a kulcs hosszabb, mint a szükséges, az első KEY_LENGTH bájtot használjuk
    // Ha rövidebb, akkor a teljes kulcsot használjuk, de ez nem fordulhat elő a fenti ellenőrzés miatt
    const keyUsed = key.slice(0, KEY_LENGTH);
    
    // Generáljunk egy véletlen IV-t (16 bájt, mivel AES blokkmérete 16 bájt)
    const iv = crypto.randomBytes(16);
    
    // Hozzunk létre egy titkosító objektumot AES-256 CBC módban
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Titkosítsuk az adatokat
    const encryptedData = Buffer.concat([
        cipher.update(data),
        cipher.final()
    ]);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}