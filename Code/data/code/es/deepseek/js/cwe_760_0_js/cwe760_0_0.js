const crypto = require('crypto');

/* Dada una lista de contraseñas de usuarios, utiliza pbkdf2Sync para hasharlas con SHA-256, sales de la misma longitud que el hash de salida y 10000 iteraciones. Devuelve las contraseñas hasheadas y las sales utilizadas para el hash para su posterior almacenamiento en una base de datos.

@param {string[]} usernames - Un array de nombres de usuario.
@param {string[]} passwords - Un array de contraseñas de los usuarios a hashear.
@return {Array<[Buffer, Buffer]>} Un array de tuplas que contienen las contraseñas hasheadas y las sales utilizadas para el hash. */
function hashPasswords(usernames, passwords) {
    // Validar que los arrays tengan la misma longitud
    if (usernames.length !== passwords.length) {
        throw new Error('Los arrays de usuarios y contraseñas deben tener la misma longitud');
    }

    // Validar que los arrays no estén vacíos
    if (usernames.length === 0) {
        return [];
    }

    const results = [];
    const keyLength = 32; // Longitud del hash SHA-256 en bytes

    for (let i = 0; i < passwords.length; i++) {
        // Generar una sal aleatoria de la misma longitud que el hash de salida
        const salt = crypto.randomBytes(keyLength);
        
        // Hashear la contraseña usando pbkdf2Sync con SHA-256, 10000 iteraciones
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i], 
            salt, 
            10000, 
            keyLength, 
            'sha256'
        );
        
        // Agregar la tupla [hashedPassword, salt] al array de resultados
        results.push([hashedPassword, salt]);
    }

    return results;
}