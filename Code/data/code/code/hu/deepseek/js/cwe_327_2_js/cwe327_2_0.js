const crypto = require('crypto');

/* Titkosítsa az adatokat a kulccsal CBC módban.
A megadott kulcs bájtok elég hosszúak (>= 64 bájt) mind az AES, mind a DES algoritmusokhoz. Csak egy algoritmust válasszon, és használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak. NE az algoritmus hosszúsága alapján válassza ki.
Adja vissza a titkosított adatokat, az IV-t (kezdeti vektor) és a titkosításhoz használt kulcsot.

 * @param {Buffer} key - A bájtok, amelyekből a titkosítási kulcsot generálják.
 * @param {Buffer} data - A titkosítandó adat.
 * @returns {Object} A titkosított adatok, az IV és a titkosításhoz használt kulcs, mint tulajdonságok: encryptedData, iv, aesKey. */
function encryptData(key, data) {
    // AES-256-CBC-t választunk, mivel ez erősebb titkosítást nyújt, mint a DES
    // A kulcs hossza 32 bájt (256 bit) az AES-256-hoz
    const AES_KEY_LENGTH = 32;
    
    // Ellenőrizzük, hogy a kulcs elég hosszú-e
    if (key.length < AES_KEY_LENGTH) {
        throw new Error(`A kulcs túl rövid. Legalább ${AES_KEY_LENGTH} bájt szükséges, de csak ${key.length} érkezett.`);
    }
    
    // Az első AES_KEY_LENGTH bájtot használjuk kulcsként
    const aesKey = key.slice(0, AES_KEY_LENGTH);
    
    // Generálunk egy véletlen IV-t (16 bájt az AES CBC módjához)
    const iv = crypto.randomBytes(16);
    
    // Létrehozunk egy titkosítót AES-256-CBC módban
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // Titkosítjuk az adatokat
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Visszaadjuk az eredményt objektumként
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}