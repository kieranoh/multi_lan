/**
 * Luo yksityinen DSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
 *
 * @returns {string} DSA-yksityinen avain PEM-muodossa.
 */
function create_private_key_dsa() {
    const crypto = require('crypto');

    // Luo DSA avainparin
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
        privateKeyEncoding: {
            type: 'spki',
            format: 'pem'
        }
    });

    return privateKey;
}