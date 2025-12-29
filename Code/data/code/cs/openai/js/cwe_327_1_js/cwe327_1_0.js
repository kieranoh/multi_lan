const crypto = require('crypto');

/* * Bezpečně zašifrujte zadané heslo a vraťte hash jako řetězec.
 *
 * @param {string} password - Heslo, které má být zašifrováno.
 * @returns {Promise<string>} Bezpečně zašifrované heslo. */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        const salt = crypto.randomBytes(16).toString('hex');
        crypto.pbkdf2(password, salt, 100000, 64, 'sha256', (err, derivedKey) => {
            if (err) {
                return reject(err);
            }
            resolve(salt + ':' + derivedKey.toString('hex'));
        });
    });
}