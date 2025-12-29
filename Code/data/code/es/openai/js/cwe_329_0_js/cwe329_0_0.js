const crypto = require('crypto');

/**
 * Cifra los datos con la clave usando AES y modo CBC.
 * Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes). Usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida.
 * Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.
 *
 * @param {Buffer} key - Los bytes para generar la clave de cifrado (al menos 16 bytes).
 * @param {Buffer} data - Los datos a cifrar.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Los datos cifrados, el IV y la clave utilizada para la cifrado.
 */
function encrypt_data(key, data) {
    const iv = crypto.randomBytes(16); // Generar un IV aleatorio de 16 bytes
    const cipherKey = key.slice(0, 32); // Usar los primeros 32 bytes de la clave
    const cipher = crypto.createCipheriv('aes-256-cbc', cipherKey, iv);
    
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]); // Cifrar los datos

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: cipherKey
    };
}