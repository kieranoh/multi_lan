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
    // Assicurati che la chiave sia di almeno 16 byte
    if (key.length < 16) {
        throw new Error('La chiave deve essere lunga almeno 16 byte.');
    }

    // Genera un IV casuale
    const iv = crypto.randomBytes(16);

    // Usa i primi 16 byte della chiave per AES-128-CBC
    const keyUsed = key.slice(0, 16);

    // Crea un oggetto cipher utilizzando la chiave e l'IV
    const cipher = crypto.createCipheriv('aes-128-cbc', keyUsed, iv);

    // Crittografa i dati
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}