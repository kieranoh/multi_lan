const crypto = require('crypto');

/**
 * A megadott jelszót biztonságosan hasheljük, és a hash-t stringként adjuk vissza.
 *
 * @param {string} password - A hashelendő jelszó.
 * @returns {Promise<string>} A biztonságosan hashelt jelszó.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Véletlenszerű só generálása
            const salt = crypto.randomBytes(16).toString('hex');
            
            // PBKDF2 hashelés 100,000 iterációval, 64 bájtos kulcs hosszal, SHA-512 hash függvénnyel
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                } else {
                    // A sót és a hash-t együtt tároljuk a következő formátumban: salt:hash
                    const hash = derivedKey.toString('hex');
                    const result = `${salt}:${hash}`;
                    resolve(result);
                }
            });
        } catch (error) {
            reject(error);
        }
    });
}