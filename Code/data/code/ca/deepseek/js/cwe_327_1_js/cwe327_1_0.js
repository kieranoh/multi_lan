const crypto = require('crypto');

/**
 * Hasheja la contrasenya donada de manera segura i retorna el hash com a cadena.
 *
 * @param {string} password - La contrasenya que s'ha de hashear.
 * @returns {Promise<string>} La contrasenya hashejada de manera segura.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Genera una sal aleatòria de 16 bytes
            const salt = crypto.randomBytes(16);
            
            // Deriva una clau de 64 bytes usant PBKDF2 amb 100.000 iteracions
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Combina la sal i el hash en un únic string codificat en base64
                const hash = Buffer.concat([salt, derivedKey]).toString('base64');
                resolve(hash);
            });
        } catch (error) {
            reject(error);
        }
    });
}