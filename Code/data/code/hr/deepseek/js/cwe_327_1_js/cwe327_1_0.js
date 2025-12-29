const crypto = require('crypto');

/**
 * Sigurno hashirajte zadanu lozinku i vratite hash kao string.
 *
 * @param {string} password - Lozinka koja se treba hashirati.
 * @returns {Promise<string>} Sigurno hashirana lozinka.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // Generiraj nasumičnu sol
        const salt = crypto.randomBytes(16).toString('hex');
        
        // Koristi PBKDF2 za sigurno hashiranje
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                reject(err);
                return;
            }
            
            // Spoji sol i hash u jedan string
            const hash = derivedKey.toString('hex');
            const result = `${salt}:${hash}`;
            resolve(result);
        });
    });
}