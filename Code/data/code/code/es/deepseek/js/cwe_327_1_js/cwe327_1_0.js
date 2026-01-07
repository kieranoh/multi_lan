const crypto = require('crypto');

/**
 * Hashea la contraseña dada de forma segura y devuelve el hash como una cadena.
 *
 * @param {string} password - La contraseña que se va a hashear.
 * @returns {Promise<string>} La contraseña hasheada de forma segura.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Generar una sal aleatoria de 16 bytes
            const salt = crypto.randomBytes(16);
            
            // Usar PBKDF2 para derivar una clave de la contraseña
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Combinar sal y hash en un formato: salt:hash (ambos en hex)
                const hash = derivedKey.toString('hex');
                const saltHex = salt.toString('hex');
                const combined = `${saltHex}:${hash}`;
                
                resolve(combined);
            });
        } catch (error) {
            reject(error);
        }
    });
}