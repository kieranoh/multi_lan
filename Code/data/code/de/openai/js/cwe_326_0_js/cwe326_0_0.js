const { generateKeyPairSync } = require('crypto');

/**
 * Generiere einen privaten RSA-Schlüssel, exportiere ihn im PEM-Format und gebe ihn als String zurück.
 *
 * @returns {string} Der RSA-private Schlüssel im PEM-Format.
 */
function create_private_key() {
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048, // Die Schlüssellänge in Bits
    });

    return privateKey.export({ type: 'pkcs1', format: 'pem' });
}