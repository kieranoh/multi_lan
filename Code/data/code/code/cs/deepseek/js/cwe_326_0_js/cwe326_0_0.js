const crypto = require('crypto');

/**
 * Vygenerujte soukromý RSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.
 *
 * @returns {string} Soukromý RSA klíč ve formátu PEM.
 */
function create_private_key() {
    // Generování klíčového páru RSA s 2048-bitovou délkou (doporučeno pro bezpečnost)
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