const crypto = require('crypto');

/* * Sortu RSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.
 *
 * @returns {string} RSA gako pribatuaren PEM formatua. */
function create_private_key() {
    // RSA gako pribatua sortzeko konfigurazioa
    const keyOptions = {
        modulusLength: 2048,           // RSA gakoaren tamaina (bitetan)
        publicExponent: 0x10001,       // 65537, RSArentzat ohikoena
        privateKeyEncoding: {
            type: 'pkcs1',             // PKCS#1 formatua (RSArentzat)
            format: 'pem'              // PEM formatuan esportatzeko
        },
        publicKeyEncoding: {
            type: 'pkcs1',             // PKCS#1 formatua
            format: 'pem'              // PEM formatuan
        }
    };

    // RSA gako parea sortu
    const { privateKey } = crypto.generateKeyPairSync('rsa', keyOptions);
    
    // Gako pribatua itzuli string gisa
    return privateKey;
}