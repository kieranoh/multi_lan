const crypto = require('crypto');

/**
 * Bezpečně zašifrujte zadané heslo a vraťte hash jako řetězec.
 *
 * @param {string} password - Heslo, které má být zašifrováno.
 * @returns {Promise<string>} Bezpečně zašifrované heslo.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Vytvoření náhodné soli
            const salt = crypto.randomBytes(16).toString('hex');
            
            // Vytvoření hash pomocí PBKDF2 s 100,000 iteracemi
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Kombinace soli a hash do jednoho řetězce
                const hash = derivedKey.toString('hex');
                const combined = `${salt}:${hash}`;
                resolve(combined);
            });
        } catch (error) {
            reject(error);
        }
    });
}