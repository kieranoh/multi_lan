const crypto = require('crypto');

/**
 * Genera una chiave DSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
 *
 * @returns {string} La chiave DSA privata in formato PEM.
 */
function create_private_key_dsa() {
    try {
        // Genera una coppia di chiavi DSA con parametri standard
        const { privateKey } = crypto.generateKeyPairSync('dsa', {
            modulusLength: 2048,  // Lunghezza del modulo in bit
            divisorLength: 256,   // Lunghezza del divisore in bit (parametro q)
        });

        // Esporta la chiave privata in formato PEM
        const pemPrivateKey = privateKey.export({
            type: 'pkcs8',
            format: 'pem'
        });

        return pemPrivateKey;
    } catch (error) {
        // Gestione elegante degli errori
        throw new Error(`Errore nella generazione della chiave DSA: ${error.message}`);
    }
}