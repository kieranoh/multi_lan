const crypto = require('crypto');

/**
 * A megadott jelszót biztonságosan hasheljük, és a hash-t stringként adjuk vissza.
 *
 * @param {string} password - A hashelendő jelszó.
 * @returns {Promise<string>} A biztonságosan hashelt jelszó.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        const salt = crypto.randomBytes(16).toString('hex');
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                return reject(err);
            }
            resolve(salt + ':' + derivedKey.toString('hex'));
        });
    });
}