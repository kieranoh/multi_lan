const crypto = require('crypto');

/**
 * Sortu DSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.
 *
 * @returns {string} DSA gako pribatuaren PEM formatuan.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('dsa', {
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