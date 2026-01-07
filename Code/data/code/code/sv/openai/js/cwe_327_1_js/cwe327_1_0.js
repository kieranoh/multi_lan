const crypto = require('crypto');

/**
 * Hasha det angivna lösenordet säkert och returnera hashvärdet som en sträng.
 *
 * @param {string} password - Lösenordet som ska hashas.
 * @returns {Promise<string>} Det säkert hashade lösenordet.
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