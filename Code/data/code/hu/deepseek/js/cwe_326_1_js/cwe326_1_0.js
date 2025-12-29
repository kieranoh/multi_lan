const crypto = require('crypto');

/**
 * Generálj egy privát DSA kulcsot, exportáld PEM formátumban, és térj vissza egy stringgel.
 *
 * @returns {string} A DSA privát kulcs PEM formátumban.
 */
function create_private_key_dsa() {
    // DSA kulcs generálása 2048 bites kulcshosszal
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
        divisorLength: 256, // Q mérete, ajánlott 160-256 bit között
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