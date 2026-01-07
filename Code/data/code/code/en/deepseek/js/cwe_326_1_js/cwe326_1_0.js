const crypto = require('crypto');

/**
 * Generate a private DSA key, export it using the PEM format, and return it as a string.
 *
 *
 * @returns {string} The DSA private key in PEM format.
 */
function create_private_key_dsa() {
    try {
        // Generate DSA key pair with 2048-bit modulus and 256-bit subgroup (q)
        const { privateKey } = crypto.generateKeyPairSync('dsa', {
            modulusLength: 2048,
            divisorLength: 256,
            publicKeyEncoding: {
                type: 'spki',
                format: 'pem'
            },
            privateKeyEncoding: {
                type: 'pkcs8',
                format: 'pem'
            }
        });
        
        // Return the private key in PEM format
        return privateKey;
    } catch (error) {
        // Gracefully handle any errors and return an empty string
        console.error('Error generating DSA private key:', error.message);
        return '';
    }
}