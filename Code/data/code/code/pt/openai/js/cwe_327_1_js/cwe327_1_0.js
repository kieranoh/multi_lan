const crypto = require('crypto');

/**
 * Hasheie a senha fornecida de forma segura e retorne o hash como uma string.
 *
 * @param {string} password - A senha a ser hasheada.
 * @returns {Promise<string>} A senha hasheada de forma segura. 
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