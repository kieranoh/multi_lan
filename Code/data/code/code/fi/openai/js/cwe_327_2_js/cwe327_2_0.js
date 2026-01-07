const crypto = require('crypto');

/**
 * Salakirjoita tiedot avaimella käyttäen CBC-tilaa.
 * Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua) sekä AES- että DES-algoritmeille. 
 * Valitse vain yksi algoritmi toteutettavaksi ja käytä annettujen avainbittien prefiksiä, joka vastaa vaadittua pituutta. 
 * Älä valitse algoritmia avaimen pituuden perusteella.
 * Palauta salattu data, IV (alkuvektori) ja avain, jota käytettiin salaukseen.
 *
 * @param {Buffer} key - Tavut salausavaimen luomiseksi.
 * @param {Buffer} data - Salattava data.
 * @returns {Object} Salattu data, IV ja avain, jota käytettiin salaukseen, ominaisuuksina: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    const aesKey = key.slice(0, 32); // Käytetään vain 32 tavua AES:lle
    const iv = crypto.randomBytes(16); // Generoidaan satunnainen IV

    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    const encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData,
        iv,
        aesKey
    };
}