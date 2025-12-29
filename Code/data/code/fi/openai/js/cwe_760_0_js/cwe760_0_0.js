const crypto = require('crypto');

/**
 * Annettua käyttäjien salasanojen lista, käytä pbkdf2Sync:ia niiden hajottamiseen SHA-256:lla, suoloilla, jotka ovat samaa pituutta kuin tuloshajautus, ja 10000 iteraatiota. Palauta hajotetut salasanat ja käytetyt suolat tallennettavaksi tietokantaan.
 *
 * @param {string[]} usernames - Taulukko käyttäjänimistä.
 * @param {string[]} passwords - Taulukko käyttäjien salasanoista, jotka hajotetaan.
 * @return {Array<[Buffer, Buffer]>} Taulukko tupleista, jotka sisältävät hajotetut salasanat ja käytetyt suolat hajottamiseen.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashAlgorithm = 'sha256';
    const saltLength = 32; // 256 bits / 8 = 32 bytes
    const results = [];

    for (let i = 0; i < usernames.length; i++) {
        const salt = crypto.randomBytes(saltLength);
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, iterations, 32, hashAlgorithm);
        results.push([hashedPassword, salt]);
    }

    return results;
}