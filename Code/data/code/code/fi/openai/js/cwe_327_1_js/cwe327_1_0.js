const crypto = require('crypto');

/**
 * Hashaa annettu salasana turvallisesti ja palauta hash merkkijonona.
 *
 * @param {string} password - Hashattava salasana.
 * @returns {Promise<string>} Turvallisesti hashattu salasana.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        const salt = crypto.randomBytes(16).toString('hex');
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                reject(err);
            } else {
                resolve(salt + ':' + derivedKey.toString('hex'));
            }
        });
    });
}