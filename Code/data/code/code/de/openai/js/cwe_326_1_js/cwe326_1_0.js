const crypto = require('crypto');

/**
 * Generiere einen privaten DSA-Schlüssel, exportiere ihn im PEM-Format und gebe ihn als String zurück.
 *
 * @returns {string} Der DSA-Private-Key im PEM-Format.
 */
function create_private_key_dsa() {
    // Erzeuge ein DSA-Schlüsselpaar
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // Schlüssellänge
    });

    // Exportiere den privaten Schlüssel im PEM-Format
    const pemPrivateKey = privateKey.export({
        type: 'pkcs8',
        format: 'pem',
    });

    return pemPrivateKey;
}