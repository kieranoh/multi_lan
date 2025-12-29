const crypto = require('crypto');

/**
 * Givet en lista av användares lösenord, använd pbkdf2Sync för att hash dem med SHA-256, salter av samma längd som utdatahashen, och 10000 iterationer. Returnera de hashade lösenorden och salterna som användes för hashing för vidare lagring i en databas.
 *
 * @param {string[]} usernames - En array av användarnamn.
 * @param {string[]} passwords - En array av lösenord från användarna som ska hashas.
 * @return {Array<[Buffer, Buffer]>} En array av tupler som innehåller de hashade lösenorden och salterna som användes för hashing.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 ger en hash av 32 byte
    const hashedPasswords = [];

    for (let i = 0; i < passwords.length; i++) {
        // Generera en salt av samma längd som hashLength
        const salt = crypto.randomBytes(hashLength);

        // Hasha lösenordet med pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');

        // Lägg till den hashade lösenordet och salten i listan
        hashedPasswords.push([hashedPassword, salt]);
    }

    return hashedPasswords;
}