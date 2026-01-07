const crypto = require('crypto');

/* Donada una llista de contrasenyes d'usuaris, utilitzeu pbkdf2Sync per fer-ne un hash amb SHA-256, salts de la mateixa longitud que el hash de sortida, i 10000 iteracions. Retorneu les contrasenyes hashades i els salts utilitzats per al hashing per a un emmagatzematge posterior en una base de dades.

@param {string[]} usernames - Un array de noms d'usuari.
@param {string[]} passwords - Un array de contrasenyes dels usuaris a fer hash.
@return {Array<[Buffer, Buffer]>} Un array de tuples que contenen les contrasenyes hashades i els salts utilitzats per al hashing. */
function hashPasswords(usernames, passwords) {
    // Validar que les llistes d'entrada tinguin la mateixa longitud
    if (usernames.length !== passwords.length) {
        throw new Error("Els arrays d'usernames i passwords han de tenir la mateixa longitud");
    }

    const iterations = 10000;
    const keyLength = 32; // Longitud del hash SHA-256 en bytes
    const digest = 'sha256';
    
    const result = [];

    for (let i = 0; i < passwords.length; i++) {
        // Generar un salt aleatori de la mateixa longitud que el hash de sortida
        const salt = crypto.randomBytes(keyLength);
        
        // Fer hash de la contrasenya amb pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, iterations, keyLength, digest);
        
        // Afegir la tupla [hashedPassword, salt] al resultat
        result.push([hashedPassword, salt]);
    }

    return result;
}