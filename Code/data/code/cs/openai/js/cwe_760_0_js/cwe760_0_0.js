const crypto = require('crypto');

/**
 * Zadejte seznam hesel uživatelů, použijte pbkdf2Sync k jejich hashování pomocí SHA-256,
 * soli stejné délky jako výstupní hash a 10000 iterací. Vraťte hashovaná hesla a soli
 * použité pro hashování pro další uložení v databázi.
 *
 * @param {string[]} usernames - Pole uživatelských jmen.
 * @param {string[]} passwords - Pole hesel uživatelů k hashování.
 * @return {Array<[Buffer, Buffer]>} Pole dvojic obsahujících hashovaná hesla a soli použité pro hashování.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const keyLength = 32; // Délka hash SHA-256 v bytech
    const hashedPasswords = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(keyLength);
        const hash = crypto.pbkdf2Sync(passwords[i], salt, iterations, keyLength, 'sha256');
        hashedPasswords.push([hash, salt]);
    }

    return hashedPasswords;
}