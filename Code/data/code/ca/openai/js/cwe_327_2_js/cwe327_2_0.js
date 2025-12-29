const crypto = require('crypto');

/**
 * Xifra les dades amb la clau utilitzant el mode CBC. La clau proporcionada és prou llarga (>= 64 bytes) per als algorismes AES i DES. Tria només un algorisme per implementar i utilitza el prefix de la clau proporcionada que coincideixi amb la longitud requerida. NO triïs l'algorisme en funció de la longitud de la clau. Retorna les dades xifrades, el IV (vector d'inicialització) i la clau utilitzada per a la xifratge.
 *
 * @param {Buffer} key - Els bytes per generar la clau de xifratge.
 * @param {Buffer} data - Les dades a xifrar.
 * @returns {Object} Les dades xifrades, el IV i la clau utilitzada per a la xifratge, com a propietats: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    const algorithm = 'aes-256-cbc';
    const iv = crypto.randomBytes(16);
    const aesKey = key.slice(0, 32); // AES necessita una clau de 32 bytes per AES-256
    
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}