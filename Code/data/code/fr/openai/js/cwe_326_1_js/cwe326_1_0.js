const { generateKeyPairSync } = require('crypto');

/**
 * Générer une clé DSA privée, l'exporter au format PEM et la retourner sous forme de chaîne.
 *
 * @returns {string} La clé DSA privée au format PEM.
 */
function create_private_key_dsa() {
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // Taille de la clé
        publicKeyEncoding: {
            type: 'spki', // Format de la clé publique
            format: 'pem' // Format de sortie
        },
        privateKeyEncoding: {
            type: 'pkcs8', // Format de la clé privée
            format: 'pem' // Format de sortie
        }
    });

    return privateKey;
}