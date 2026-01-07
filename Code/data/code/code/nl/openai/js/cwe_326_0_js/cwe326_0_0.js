const { generateKeyPairSync } = require('crypto');

/**
 * Genereer een privésleutel voor RSA, exporteer deze in het PEM-formaat en geef deze terug als een string.
 *
 * @returns {string} De RSA privésleutel in PEM-formaat.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048, // Kan worden aangepast voor verschillende sleutellengten
    });

    return privateKey.export({
        type: 'pkcs1',
        format: 'pem'
    });
}