const { generateKeyPairSync } = require('crypto');

/**
 * Générer une clé RSA privée, l'exporter au format PEM et la retourner sous forme de chaîne.
 *
 * @returns {string} La clé RSA privée au format PEM.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048, // Longueur de clé recommandée
    });

    // Exporter la clé privée au format PEM
    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}