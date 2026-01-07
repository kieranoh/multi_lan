const crypto = require('crypto');

/**
 * Dada una lista de contraseñas de usuarios, utiliza pbkdf2Sync para hasharlas con SHA-256, 
 * sales de la misma longitud que el hash de salida y 10000 iteraciones. Devuelve las contraseñas 
 * hasheadas y las sales utilizadas para el hash para su posterior almacenamiento en una base de datos.
 *
 * @param {string[]} usernames - Un array de nombres de usuario.
 * @param {string[]} passwords - Un array de contraseñas de los usuarios a hashear.
 * @return {Array<[Buffer, Buffer]>} Un array de tuplas que contienen las contraseñas hasheadas 
 *         y las sales utilizadas para el hash.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 produce un hash de 32 bytes
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(hashLength);
        const hash = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');
        results.push([hash, salt]);
    }

    return results;
}