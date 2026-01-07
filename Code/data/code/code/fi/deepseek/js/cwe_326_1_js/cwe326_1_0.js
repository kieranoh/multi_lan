const crypto = require('crypto');

/**
 * Luo yksityinen DSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
 *
 * @returns {string} DSA-yksityinen avain PEM-muodossa.
 */
function create_private_key_dsa() {
    // Luodaan DSA-avainpari (2048-bittinen, SHA-256)
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
}