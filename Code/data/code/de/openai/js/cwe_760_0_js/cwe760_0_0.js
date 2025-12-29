const crypto = require('crypto');

/**
 * Gegeben ist eine Liste von Passwörtern der Benutzer, verwende pbkdf2Sync, um sie mit SHA-256, Salzen der gleichen Länge wie der Ausgabe-Hash und 10000 Iterationen zu hashen. Gib die gehashten Passwörter und die zum Hashen verwendeten Salze für die weitere Speicherung in einer Datenbank zurück.
 *
 * @param {string[]} usernames - Ein Array von Benutzernamen.
 * @param {string[]} passwords - Ein Array von Passwörtern der Benutzer, die gehasht werden sollen.
 * @return {Array<[Buffer, Buffer]>} Ein Array von Tupeln, das die gehashten Passwörter und die zum Hashen verwendeten Salze enthält.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 produces 32 bytes hash
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(hashLength);
        const hash = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');
        results.push([hash, salt]);
    }

    return results;
}