const crypto = require('crypto');

/* Xifra les dades amb la clau utilitzant el mode CBC. La clau proporcionada és prou llarga (>= 64 bytes) per als algorismes AES i DES. Tria només un algorisme per implementar i utilitza el prefix de la clau proporcionada que coincideixi amb la longitud requerida. NO triïs l'algorisme en funció de la longitud de la clau. Retorna les dades xifrades, el IV (vector d'inicialització) i la clau utilitzada per a la xifratge.

 * @param {Buffer} key - Els bytes per generar la clau de xifratge.
 * @param {Buffer} data - Les dades a xifrar.
 * @returns {Object} Les dades xifrades, el IV i la clau utilitzada per a la xifratge, com a propietats: encryptedData, iv, aesKey. */
function encryptData(key, data) {
    // Triem AES-256-CBC com a algorisme (256 bits = 32 bytes)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 32 bytes per a AES-256
    
    // Utilitzem els primers 32 bytes de la clau proporcionada
    const aesKey = key.slice(0, keyLength);
    
    // Generem un IV aleatori de 16 bytes (mida estàndard per a AES)
    const iv = crypto.randomBytes(16);
    
    // Creem el xifrador
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Xifrem les dades
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    // Retornem l'objecte amb les dades xifrades, IV i clau utilitzada
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}