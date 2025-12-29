const crypto = require('crypto');

/**
 * A felhasználók jelszavainak listáját figyelembe véve, használd a pbkdf2Sync-t a SHA-256-tal való hasheléshez, az output hash-hez hasonló hosszúságú sókkal, és 10000 iterációval. Térj vissza a hashelt jelszavakkal és a hasheléshez használt sókkal, hogy azokat további tárolásra egy adatbázisban felhasználhasd.
 *
 * @param {string[]} usernames - Felhasználónevek tömbje.
 * @param {string[]} passwords - A hasheléshez használandó felhasználói jelszavak tömbje.
 * @return {Array<[Buffer, Buffer]>} A hashelt jelszavakat és a hasheléshez használt sókat tartalmazó tuple-ök tömbje.
 */
function hashPasswords(usernames, passwords) {
    const result = [];
    
    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(32); // Generálj 32 bájt hosszúságú sót
        const hash = crypto.pbkdf2Sync(passwords[i], salt, 10000, 64, 'sha256');
        result.push([hash, salt]);
    }
    
    return result;
}