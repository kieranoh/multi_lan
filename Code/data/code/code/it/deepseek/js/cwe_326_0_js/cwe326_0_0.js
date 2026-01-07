const crypto = require('crypto');

/**
 * Genera una chiave RSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
 *
 * @returns {string} La chiave privata RSA in formato PEM.
 */
function create_private_key() {
    try {
        // Genera una coppia di chiavi RSA con 2048 bit (dimensione standard)
        const { privateKey } = crypto.generateKeyPairSync('rsa', {
            modulusLength: 2048,
            publicKeyEncoding: {
                type: 'spki',
                format: 'pem'
            },
            privateKeyEncoding: {
                type: 'pkcs8',
                format: 'pem'
            }
        });
        
        return privateKey;
    } catch (error) {
        // Gestione elegante degli errori
        console.error('Errore nella generazione della chiave privata:', error.message);
        throw new Error('Impossibile generare la chiave privata RSA');
    }
}