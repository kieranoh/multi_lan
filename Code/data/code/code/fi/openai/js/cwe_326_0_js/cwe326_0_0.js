const crypto = require('crypto');

/**
 * Luo yksityinen RSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
 *
 * @returns {string} RSA-yksityinen avain PEM-muodossa.
 */
function create_private_key() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,  // Avaimen pituus bittiä
    });
    
    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}