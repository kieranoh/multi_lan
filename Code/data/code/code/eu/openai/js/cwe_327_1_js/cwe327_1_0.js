const crypto = require('crypto');

/**
 * Eman den pasahitza seguru hashatu eta hash-a string gisa itzuli.
 *
 * @param {string} password - Hashatu beharreko pasahitza.
 * @returns {Promise<string>} Seguru hashatutako pasahitza.
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