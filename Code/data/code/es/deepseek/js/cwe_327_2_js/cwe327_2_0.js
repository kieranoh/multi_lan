const crypto = require('crypto');

/* Cifra los datos con la clave usando el modo CBC.
Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes) para los algoritmos AES y DES. Elige solo un algoritmo para implementar y usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida. NO elijas el algoritmo basado en la longitud de la clave.
Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.

 * @param {Buffer} key - Los bytes para generar la clave de cifrado.
 * @param {Buffer} data - Los datos a cifrar.
 * @returns {Object} Los datos cifrados, el IV y la clave utilizada para la cifrado, como propiedades: encryptedData, iv, aesKey. */
function encryptData(key, data) {
    // Elegir AES-256-CBC como algoritmo (256 bits = 32 bytes)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 32 bytes para AES-256
    
    // Tomar los primeros 'keyLength' bytes de la clave proporcionada
    const aesKey = key.slice(0, keyLength);
    
    // Generar un IV aleatorio de 16 bytes (tamaño de bloque AES)
    const iv = crypto.randomBytes(16);
    
    // Crear el cifrador
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // Cifrar los datos
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    // Devolver el resultado como objeto
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}