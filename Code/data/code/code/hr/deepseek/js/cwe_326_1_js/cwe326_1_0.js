const crypto = require('crypto');

/**
 * Generirajte privatni DSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.
 *
 * @returns {string} Privatni DSA ključ u PEM formatu.
 */
function create_private_key_dsa() {
    // Generiranje DSA parametara (ključevi za 2048-bitni DSA)
    const dsaParams = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
        divisorLength: 256, // Q veličina preporučena za 2048-bitni DSA
    });

    // Izvoz privatnog ključa u PEM formatu
    const privateKeyPEM = dsaParams.privateKey.export({
        type: 'pkcs8',
        format: 'pem'
    });

    return privateKeyPEM;
}