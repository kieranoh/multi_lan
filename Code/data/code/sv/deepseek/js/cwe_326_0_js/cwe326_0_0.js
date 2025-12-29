const crypto = require('crypto');

/**
 * Generera en privat RSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.
 *
 * @returns {string} Den privata RSA-nyckeln i PEM-format.
 */
function create_private_key() {
    // Generera ett nyckelpar med specifika parametrar
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048,          // RSA-nyckelstorlek i bitar
        publicKeyEncoding: {
            type: 'pkcs1',            // PKCS#1 format för publik nyckel
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs1',            // PKCS#1 format för privat nyckel
            format: 'pem'
        }
    });
    
    return privateKey;
}