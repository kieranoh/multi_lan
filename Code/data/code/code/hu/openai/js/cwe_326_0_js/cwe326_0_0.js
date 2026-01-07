const { generateKeyPairSync } = require('crypto');

/**
 * Generálj egy privát RSA kulcsot, exportáld PEM formátumban, és térj vissza egy stringgel.
 *
 * @returns {string} A RSA privát kulcs PEM formátumban.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });
    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}