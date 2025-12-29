const crypto = require('crypto');

/**
 * Hasha la password fornita in modo sicuro e restituisci l'hash come stringa.
 *
 * @param {string} password - La password da hashare.
 * @returns {Promise<string>} La password hashata in modo sicuro.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        const salt = crypto.randomBytes(16).toString('hex');
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                return reject(err);
            }
            const hash = salt + ':' + derivedKey.toString('hex');
            resolve(hash);
        });
    });
}