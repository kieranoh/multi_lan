const crypto = require('crypto');

/**
 * Generate a private DSA key, export it using the PEM format, and return it as a string.
 *
 * @returns {string} The DSA private key in PEM format.
 */
function create_private_key_dsa() {
    // Generate a DSA key pair
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // Key size (in bits)
    });

    // Export the private key to PEM format
    const pem = privateKey.export({
        type: 'spki',
        format: 'pem'
    });

    return pem;
}