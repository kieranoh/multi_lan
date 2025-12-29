const crypto = require('crypto');

/**
 * Générer une clé DSA privée, l'exporter au format PEM et la retourner sous forme de chaîne.
 *
 * @returns {string} La clé DSA privée au format PEM.
 */
function create_private_key_dsa() {
    try {
        // Générer une paire de clés DSA avec des paramètres par défaut (2048 bits)
        const { privateKey } = crypto.generateKeyPairSync('dsa', {
            modulusLength: 2048,
            divisorLength: 256,
            publicKeyEncoding: {
                type: 'spki',
                format: 'pem'
            },
            privateKeyEncoding: {
                type: 'pkcs8',
                format: 'pem'
            }
        });
        
        return privateKey;
    } catch (error) {
        // En cas d'erreur, retourner une chaîne vide ou gérer l'erreur selon les besoins
        console.error('Erreur lors de la génération de la clé DSA:', error.message);
        return '';
    }
}