const crypto = require('crypto');

/**
 * Zabezpiecz podane hasło i zwróć hash jako ciąg znaków.
 *
 * @param {string} password - Hasło do zhashowania.
 * @returns {Promise<string>} Bezpiecznie zhashowane hasło. 
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