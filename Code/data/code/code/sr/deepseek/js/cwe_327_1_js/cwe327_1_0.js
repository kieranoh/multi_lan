const crypto = require('crypto');

/**
 * Sigurno hash-ujte dati password i vratite hash kao string.
 *
 * @param {string} password - Password koji treba hash-ovati.
 * @returns {Promise<string>} Sigurno hash-ovani password.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // Generisanje nasumične soli
        const salt = crypto.randomBytes(16).toString('hex');
        
        // Hash-ovanje passworda sa soli koristeći PBKDF2
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                reject(err);
                return;
            }
            
            // Formatiranje hash-a: salt:hash
            const hash = derivedKey.toString('hex');
            const combined = `${salt}:${hash}`;
            resolve(combined);
        });
    });
}