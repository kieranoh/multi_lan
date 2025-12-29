const crypto = require('crypto');

/**
 * Cifra los datos con la clave usando el modo CBC.
 * Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes) para los algoritmos AES y DES. 
 * Elige solo un algoritmo para implementar y usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida. 
 * NO elijas el algoritmo basado en la longitud de la clave.
 * Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.
 *
 * @param {Buffer} key - Los bytes para generar la clave de cifrado.
 * @param {Buffer} data - Los datos a cifrar.
 * @returns {Object} Los datos cifrados, el IV y la clave utilizada para la cifrado, como propiedades: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Seleccionamos el algoritmo AES, longitud de clave de 32 bytes (256 bits)
    const aesKey = key.slice(0, 32);
    const iv = crypto.randomBytes(16); // IV debe ser de 16 bytes para AES
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // Ciframos los datos
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}