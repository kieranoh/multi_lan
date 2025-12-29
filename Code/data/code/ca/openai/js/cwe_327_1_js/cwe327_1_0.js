const crypto = require('crypto');

/**
 * Hasheja la contrasenya donada de manera segura i retorna el hash com a cadena.
 *
 * @param {string} password - La contrasenya que s'ha de hashear.
 * @returns {Promise<string>} La contrasenya hashejada de manera segura.
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