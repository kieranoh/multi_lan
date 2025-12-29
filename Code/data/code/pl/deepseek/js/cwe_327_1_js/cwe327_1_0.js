const crypto = require('crypto');

/**
 * Zabezpiecz podane hasło i zwróć hash jako ciąg znaków.
 *
 * @param {string} password - Hasło do zhashowania.
 * @returns {Promise<string>} Bezpiecznie zhashowane hasło.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Generuj losową sól o długości 16 bajtów (128 bitów)
            const salt = crypto.randomBytes(16);
            
            // Użyj algorytmu PBKDF2 z 100,000 iteracjami, długością klucza 64 bajty (512 bitów)
            // i funkcją skrótu SHA-512
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Format: algorytm:iteracje:sól:hash (wszystko zakodowane w base64)
                const hash = `pbkdf2_sha512:100000:${salt.toString('base64')}:${derivedKey.toString('base64')}`;
                resolve(hash);
            });
        } catch (error) {
            reject(error);
        }
    });
}