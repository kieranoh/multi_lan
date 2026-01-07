const crypto = require('crypto');

/* * Vygenerujte soukromý DSA klíč, exportujte ho pomocí formátu PEM a vraťte ho jako řetězec.
 *
 * @returns {string} Soukromý DSA klíč ve formátu PEM. */
function create_private_key_dsa() {
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
    });

    return privateKey.export({ format: 'pem', type: 'spki' });
}