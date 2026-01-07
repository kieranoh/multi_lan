const crypto = require('crypto');

/**
 * Hasha det angivna lösenordet säkert och returnera hashvärdet som en sträng.
 *
 * @param {string} password - Lösenordet som ska hashas.
 * @returns {Promise<string>} Det säkert hashade lösenordet.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // Generera ett slumpmässigt salt
        const salt = crypto.randomBytes(16).toString('hex');
        
        // Använd scrypt för att hasha lösenordet
        crypto.scrypt(password, salt, 64, (err, derivedKey) => {
            if (err) {
                reject(err);
                return;
            }
            
            // Kombinera salt och hash till en sträng
            const hash = derivedKey.toString('hex');
            const result = `${salt}:${hash}`;
            resolve(result);
        });
    });
}