const crypto = require('crypto');

/**
 * Salaa tiedot avaimella käyttäen AES:ää ja CBC-tilaa.
 * Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua). Käytä annettujen avainbittien etuliitettä, joka vastaa vaadittua pituutta.
 * Palauta salatut tiedot, IV (alkuvektori) ja salauksessa käytetty avain.
 *
 * @param {Buffer} key - Tavut salausavaimen luomiseksi (vähintään 16 tavua).
 * @param {Buffer} data - Salattavat tiedot.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Salatut tiedot, IV ja salauksessa käytetty avain.
 */
function encrypt_data(key, data) {
    // Varmista, että avain on vähintään 16 tavua pitkä
    if (key.length < 16) {
        throw new Error('Avaimen pituus on vähintään 16 tavua');
    }

    // Luo satunnainen alkivektori
    const iv = crypto.randomBytes(16);

    // Luo salausobjekti
    const cipher = crypto.createCipheriv('aes-256-cbc', key.slice(0, 32), iv);

    // Salaa tiedot
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    // Palauta salatut tiedot, IV ja käytetty avain
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: key.slice(0, 32) // Palauta avain, joka on 32 tavua pitkä
    };
}