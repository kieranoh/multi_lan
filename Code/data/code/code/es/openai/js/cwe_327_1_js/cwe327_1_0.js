const crypto = require('crypto');

/**
 * Hashea la contraseña dada de forma segura y devuelve el hash como una cadena.
 *
 * @param {string} password - La contraseña que se va a hashear.
 * @returns {Promise<string>} La contraseña hasheada de forma segura.
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