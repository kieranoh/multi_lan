const crypto = require('crypto');

/**
 * Hashen Sie das angegebene Passwort sicher und geben Sie den Hash als Zeichenfolge zurück.
 *
 * @param {string} password - Das zu hashende Passwort.
 * @returns {Promise<string>} Das sicher gehashte Passwort.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Generiere ein zufälliges Salt
            const salt = crypto.randomBytes(16).toString('hex');
            
            // Erstelle einen Hash mit PBKDF2 (Password-Based Key Derivation Function 2)
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Kombiniere Salt und Hash im Format: salt:hash
                const hash = derivedKey.toString('hex');
                const result = `${salt}:${hash}`;
                resolve(result);
            });
        } catch (error) {
            reject(error);
        }
    });
}