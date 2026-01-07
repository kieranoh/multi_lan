const crypto = require('crypto');

/**
 * Generera en privat DSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.
 *
 * @returns {string} Den privata DSA-nyckeln i PEM-format.
 */
function create_private_key_dsa() {
    // Generera en DSA-nyckel
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // längd på nyckeln
    });

    // Exportera nyckeln i PEM-format
    const pem = privateKey.export({
        type: 'sec1',
        format: 'pem',
    });

    return pem;
}