const crypto = require('crypto');

/**
 * Hachez le certificat donné de manière sécurisée et renvoyez le hachage sous forme de chaîne hexadécimale.
 *
 * @param {string} cert - Le certificat à hacher.
 * @returns {string} Le certificat haché de manière sécurisée sous forme de chaîne hexadécimale.
 */
function hash_certificate(cert) {
    // Vérifier que le certificat est une chaîne non vide
    if (typeof cert !== 'string' || cert.trim().length === 0) {
        throw new Error('Le certificat doit être une chaîne non vide');
    }

    try {
        // Créer un hachage SHA-256 (algorithme cryptographique sécurisé)
        const hash = crypto.createHash('sha256');
        
        // Mettre à jour le hachage avec le certificat
        hash.update(cert, 'utf8');
        
        // Produire le hachage sous forme hexadécimale
        return hash.digest('hex');
    } catch (error) {
        // Gérer les erreurs potentielles (par exemple, problèmes avec crypto)
        throw new Error(`Erreur lors du hachage du certificat: ${error.message}`);
    }
}