const crypto = require('crypto');

/**
 * Generálj egy privát RSA kulcsot, exportáld PEM formátumban, és térj vissza egy stringgel.
 *
 * @returns {string} A RSA privát kulcs PEM formátumban.
 */
function create_private_key() {
    // RSA kulcspár generálása 2048 bites kulcsmérettel
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048,
        publicKeyEncoding: {
            type: 'pkcs1',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs1',
            format: 'pem'
        }
    });
    
    return privateKey;
}