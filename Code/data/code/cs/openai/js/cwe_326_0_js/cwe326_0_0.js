const { generateKeyPairSync } = require('crypto');

/**
 * Vygenerujte soukromý RSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.
 *
 * @returns {string} Soukromý RSA klíč ve formátu PEM.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}