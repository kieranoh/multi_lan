const crypto = require('crypto');

/**
 * Generera en privat RSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.
 *
 * @returns {string} Den privata RSA-nyckeln i PEM-format. 
 */
function create_private_key() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({
        type: 'pkcs1',
        format: 'pem'
    });
}