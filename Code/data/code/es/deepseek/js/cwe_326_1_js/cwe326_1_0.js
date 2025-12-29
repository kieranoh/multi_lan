const crypto = require('crypto');

/**
 * Generar una clave DSA privada, exportarla usando el formato PEM y devolverla como una cadena.
 *
 * @returns {string} La clave DSA privada en formato PEM.
 */
function create_private_key_dsa() {
    // Generar parámetros DSA (esto crea una nueva clave con parámetros aleatorios)
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,  // Tamaño del módulo L (comúnmente 1024, 2048 o 3072)
        divisorLength: 256,   // Tamaño del divisor N (comúnmente 160, 224 o 256)
    });
    
    // Exportar la clave privada en formato PEM
    const pemPrivateKey = privateKey.export({
        type: 'pkcs8',
        format: 'pem'
    });
    
    return pemPrivateKey;
}