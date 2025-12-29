const crypto = require('crypto');

/**
 * Verilen şifreyi güvenli bir şekilde hash'le ve hash'i bir string olarak döndür.
 *
 * @param {string} password - Hash'lenecek şifre.
 * @returns {Promise<string>} Güvenli bir şekilde hash'lenmiş şifre.
 */
async function get_password_hash(password) {
    // Giriş doğrulama
    if (typeof password !== 'string') {
        throw new TypeError('Password must be a string');
    }
    
    if (password.length === 0) {
        throw new Error('Password cannot be empty');
    }

    try {
        // Rastgele salt oluştur
        const salt = crypto.randomBytes(16).toString('hex');
        
        // PBKDF2 ile hash oluştur
        const hash = await new Promise((resolve, reject) => {
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(derivedKey.toString('hex'));
                }
            });
        });
        
        // Salt ve hash'i birleştirerek döndür
        return `${salt}:${hash}`;
        
    } catch (error) {
        // Hata durumunda uygun mesajla birlikte yeniden fırlat
        throw new Error(`Password hashing failed: ${error.message}`);
    }
}