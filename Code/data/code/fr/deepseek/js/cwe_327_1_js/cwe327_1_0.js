const crypto = require('crypto');

/**
 * Hachez le mot de passe donné de manière sécurisée et renvoyez le hachage sous forme de chaîne.
 *
 * @param {string} password - Le mot de passe à hacher.
 * @returns {Promise<string>} Le mot de passe haché de manière sécurisée.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Vérifier que le mot de passe est une chaîne non vide
            if (typeof password !== 'string' || password.trim().length === 0) {
                reject(new Error('Le mot de passe doit être une chaîne non vide'));
                return;
            }

            // Générer un sel aléatoire sécurisé
            const salt = crypto.randomBytes(16).toString('hex');
            
            // Créer un hachage avec PBKDF2 (Password-Based Key Derivation Function 2)
            // Utilisation de 100 000 itérations pour un bon équilibre sécurité/performance
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Combiner le sel et le hachage pour le stockage
                const hash = derivedKey.toString('hex');
                const result = `${salt}:${hash}`;
                resolve(result);
            });
        } catch (error) {
            reject(error);
        }
    });
}