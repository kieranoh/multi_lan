const crypto = require('crypto');

/**
 * Cripta i dati con la chiave utilizzando la modalità CBC.
 * I byte della chiave fornita sono abbastanza lunghi (>= 64 byte) per entrambi gli algoritmi AES e DES. 
 * Scegli solo un algoritmo da implementare e utilizza il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta. 
 * NON scegliere l'algoritmo in base alla lunghezza della chiave.
 * Restituisci i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.
 *
 * @param {Buffer} key - I byte per generare la chiave di crittografia.
 * @param {Buffer} data - I dati da crittografare.
 * @returns {Object} I dati crittografati, l'IV e la chiave utilizzata per la crittografia, come proprietà: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Selezione dell'algoritmo AES e preparazione della chiave
    const aesKey = key.slice(0, 32); // AES richiede chiavi di 16, 24 o 32 byte
    const iv = crypto.randomBytes(16); // Generazione di un IV di 16 byte per AES

    // Creazione del cipher con AES in modalità CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);

    // Crittografia dei dati
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    // Restituzione dell'oggetto con i dati crittografati, IV e chiave
    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}