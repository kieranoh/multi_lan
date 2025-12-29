const crypto = require('crypto');

/**
 * Cripta i dati con la chiave utilizzando la modalità CBC.
 * I byte della chiave fornita sono abbastanza lunghi (>= 64 byte) per entrambi gli algoritmi AES e DES. 
 * Scegli solo un algoritmo da implementare e utilizza il prefisso dei byte della chiave fornita che corrisponde 
 * alla lunghezza richiesta. NON scegliere l'algoritmo in base alla lunghezza della chiave.
 * Restituisci i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.
 * 
 * @param {Buffer} key - I byte per generare la chiave di crittografia.
 * @param {Buffer} data - I dati da crittografare.
 * @returns {Object} I dati crittografati, l'IV e la chiave utilizzata per la crittografia, come proprietà: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Scelgo AES-256-CBC come algoritmo (scelta fissa, non basata sulla lunghezza della chiave)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 32 byte per AES-256
    
    // Prendo i primi keyLength byte dalla chiave fornita
    const aesKey = key.slice(0, keyLength);
    
    // Genera un IV casuale di 16 byte (dimensione IV per AES)
    const iv = crypto.randomBytes(16);
    
    // Crea il cifratore
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Cripta i dati
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // Restituisce l'oggetto con i risultati
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}