const crypto = require('crypto');

/* A felhasználók jelszavainak listáját figyelembe véve, használd a pbkdf2Sync-t a SHA-256-tal való hasheléshez, az output hash-hez hasonló hosszúságú sókkal, és 10000 iterációval. Térj vissza a hashelt jelszavakkal és a hasheléshez használt sókkal, hogy azokat további tárolásra egy adatbázisban felhasználhasd.

@param {string[]} usernames - Felhasználónevek tömbje.
@param {string[]} passwords - A hasheléshez használandó felhasználói jelszavak tömbje.
@return {Array<[Buffer, Buffer]>} A hashelt jelszavakat és a hasheléshez használt sókat tartalmazó tuple-ök tömbje. */
function hashPasswords(usernames, passwords) {
    // Ellenőrizzük, hogy a bemeneti tömbök hossza megegyezik-e
    if (usernames.length !== passwords.length) {
        throw new Error('A felhasználónevek és jelszavak tömbjének hosszának meg kell egyeznie.');
    }

    const results = [];
    const keyLength = 32; // SHA-256 hash hossza byte-okban (256 bit = 32 byte)

    for (let i = 0; i < passwords.length; i++) {
        // Generáljunk egy véletlen salt-ot, amely ugyanolyan hosszú, mint a kimeneti hash
        const salt = crypto.randomBytes(keyLength);
        
        // Hasheljük a jelszót PBKDF2-vel, SHA-256 használatával, 10000 iterációval
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, 10000, keyLength, 'sha256');
        
        // Adjuk hozzá az eredményt a tömbhöz tuple-ként
        results.push([hashedPassword, salt]);
    }

    return results;
}