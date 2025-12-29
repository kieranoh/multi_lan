const crypto = require('crypto');

/**
 * Luo yksityinen RSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
 *
 * @returns {string} RSA-yksityinen avain PEM-muodossa.
 */
function create_private_key() {
    // Luo RSA-avainpari (oletusarvoisesti 2048-bittinen)
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
    
    return privateKey;
}