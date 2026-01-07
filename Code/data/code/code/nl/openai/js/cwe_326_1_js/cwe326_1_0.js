const crypto = require('crypto');

/**
 * Genereer een privésleutel voor DSA, exporteer deze in het PEM-formaat en geef deze terug als een string.
 *
 * @returns {string} De DSA privésleutel in PEM-formaat.
 */
function create_private_key_dsa() {
    // Genereer een DSA-sleutel
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // of een andere geschikte waarde
    });

    // Exporteer de privésleutel in PEM-formaat
    const pemKey = privateKey.export({
        type: 'spki',
        format: 'pem'
    });

    return pemKey;
}