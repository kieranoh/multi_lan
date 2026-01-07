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
    // Validar que la clave tenga al menos 16 bytes
    if (key.length < 16) {
        throw new Error('La clave debe tener al menos 16 bytes');
    }

    // Usar AES-256-CBC que requiere una clave de 32 bytes
    const keyLength = 32;
    
    // Tomar el prefijo de la clave proporcionada según la longitud requerida
    const keyUsed = key.slice(0, keyLength);
    
    // Generar un IV aleatorio de 16 bytes (tamaño de bloque AES)
    const iv = crypto.randomBytes(16);
    
    // Crear el cifrador AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Cifrar los datos
    const encryptedData = Buffer.concat([
        cipher.update(data),
        cipher.final()
    ]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}