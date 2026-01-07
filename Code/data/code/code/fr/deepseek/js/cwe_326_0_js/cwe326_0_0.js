const crypto = require('crypto');

/**
 * Générer une clé RSA privée, l'exporter au format PEM et la retourner sous forme de chaîne.
 *
 * @returns {string} La clé RSA privée au format PEM.
 */
function create_private_key() {
    try {
        // Générer une paire de clés RSA avec une longueur de 2048 bits (standard sécurisé)
        const { privateKey } = crypto.generateKeyPairSync('rsa', {
            modulusLength: 2048,
            publicKeyEncoding: {
                type: 'spki',
                format: 'pem'
            },
            privateKeyEncoding: {
                type: 'pkcs8',
                format: 'pem'
            }
        });
        
        // Retourner la clé privée au format PEM
        return privateKey;
    } catch (error) {
        // En cas d'erreur, retourner une chaîne vide pour une défaillance gracieuse
        console.error('Erreur lors de la génération de la clé privée:', error.message);
        return '';
    }
}