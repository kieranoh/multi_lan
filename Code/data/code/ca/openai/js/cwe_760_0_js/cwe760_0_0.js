const crypto = require('crypto');

/**
 * Donada una llista de contrasenyes d'usuaris, utilitzeu pbkdf2Sync per fer-ne un hash amb SHA-256, salts de la mateixa longitud que el hash de sortida, i 10000 iteracions. Retorneu les contrasenyes hashades i els salts utilitzats per al hashing per a un emmagatzematge posterior en una base de dades.
 *
 * @param {string[]} usernames - Un array de noms d'usuari.
 * @param {string[]} passwords - Un array de contrasenyes dels usuaris a fer hash.
 * @return {Array<[Buffer, Buffer]>} Un array de tuples que contenen les contrasenyes hashades i els salts utilitzats per al hashing.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 produces a hash of 32 bytes
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(hashLength);
        const hash = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');
        results.push([hash, salt]);
    }

    return results;
}