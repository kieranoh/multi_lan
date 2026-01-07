const crypto = require('crypto');

/**
 * Hasha la password fornita in modo sicuro e restituisci l'hash come stringa.
 *
 * @param {string} password - La password da hashare.
 * @returns {Promise<string>} La password hashata in modo sicuro.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Genera un salt casuale
            const salt = crypto.randomBytes(16).toString('hex');
            
            // Crea l'hash della password usando PBKDF2
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Combina salt e hash in un'unica stringa
                const hash = derivedKey.toString('hex');
                const combined = `${salt}:${hash}`;
                resolve(combined);
            });
        } catch (error) {
            reject(error);
        }
    });
}