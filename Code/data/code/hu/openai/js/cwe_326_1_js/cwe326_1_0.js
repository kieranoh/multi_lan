const crypto = require('crypto');

/**
 * Generálj egy privát DSA kulcsot, exportáld PEM formátumban, és térj vissza egy stringgel.
 *
 * @returns {string} A DSA privát kulcs PEM formátumban.
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