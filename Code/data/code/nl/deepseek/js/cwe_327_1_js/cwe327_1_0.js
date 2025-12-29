const crypto = require('crypto');

/**
 * Hash het opgegeven wachtwoord veilig en retourneer de hash als een string.
 * 
 * @param {string} password - Het wachtwoord dat gehasht moet worden.
 * @returns {Promise<string>} Het veilig gehashte wachtwoord.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // Genereer een willekeurige salt van 16 bytes
        const salt = crypto.randomBytes(16);
        
        // Gebruik PBKDF2 met SHA-256, 100.000 iteraties, en een key length van 64 bytes
        crypto.pbkdf2(password, salt, 100000, 64, 'sha256', (err, derivedKey) => {
            if (err) {
                reject(err);
                return;
            }
            
            // Formatteer de hash als: salt:hash (beide base64-gecodeerd)
            const hash = derivedKey.toString('base64');
            const saltString = salt.toString('base64');
            const result = `${saltString}:${hash}`;
            
            resolve(result);
        });
    });
}