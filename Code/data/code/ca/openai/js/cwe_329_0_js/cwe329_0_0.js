const crypto = require('crypto');

/**
 * Xifra les dades amb la clau utilitzant AES i el mode CBC.
 * Els bytes de clau proporcionats són prou llargs (>= 64 bytes). Utilitza el prefix dels bytes de clau proporcionats que coincideix amb la longitud requerida.
 * Retorna les dades xifrades, l'IV (vector d'inicialització) i la clau utilitzada per a la xifrat.
 *
 * @param {Buffer} key - Els bytes per generar la clau de xifrat (almenys 16 bytes).
 * @param {Buffer} data - Les dades a xifrar.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Les dades xifrades, l'IV i la clau utilitzada per a la xifrat.
 */
function encrypt_data(key, data) {
    // Seleccionem la longitud de la clau AES (16 bytes per AES-128, 24 per AES-192, 32 per AES-256)
    const keyLength = 32; // AES-256
    const derivedKey = key.slice(0, keyLength);
    
    // Generem un IV aleatori
    const iv = crypto.randomBytes(16);
    
    // Creem un cipher amb el mètode AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', derivedKey, iv);
    
    // Xifrem les dades
    const encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: derivedKey
    };
}