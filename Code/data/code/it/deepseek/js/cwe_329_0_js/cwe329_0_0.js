const crypto = require('crypto');

/**
 * Cripta i dati con la chiave utilizzando AES e modalità CBC.
 * I byte della chiave fornita sono abbastanza lunghi (>= 64 byte). Usa il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta.
 * Restituisci i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.
 *
 * @param {Buffer} key - I byte per generare la chiave di crittografia (almeno 16 byte).
 * @param {Buffer} data - I dati da crittografare.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} I dati crittografati, l'IV e la chiave utilizzata per la crittografia.
 */
function encrypt_data(key, data) {
    // Verifica che i parametri siano Buffer
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('I parametri key e data devono essere Buffer');
    }

    // Verifica che la chiave sia almeno 16 byte
    if (key.length < 16) {
        throw new Error('La chiave deve essere di almeno 16 byte');
    }

    // AES-256-CBC richiede una chiave di 32 byte (256 bit)
    const keyLength = 32;
    
    // Usa il prefisso della chiave fornita della lunghezza richiesta
    const keyUsed = key.slice(0, keyLength);
    
    // Genera un IV casuale di 16 byte (dimensione del blocco AES)
    const iv = crypto.randomBytes(16);
    
    // Crea il cifratore AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Cripta i dati
    const encryptedData = Buffer.concat([
        cipher.update(data),
        cipher.final()
    ]);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}