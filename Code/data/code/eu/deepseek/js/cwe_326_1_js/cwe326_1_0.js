const crypto = require('crypto');

function create_private_key_dsa() {
    // DSA parametroak sortzeko konfigurazioa
    const dsaParams = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,  // L parametroa (bit-etan)
        divisorLength: 256,   // N parametroa (bit-etan)
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });

    // Gako pribatua itzuli PEM formatuan
    return dsaParams.privateKey;
}