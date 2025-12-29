const crypto = require('crypto');

/**
 * Data un elenco di password degli utenti, utilizza pbkdf2Sync per hashare con SHA-256, sali della stessa lunghezza dell'hash di output e 10000 iterazioni. Restituisci le password hashate e i sali utilizzati per l'hashing per ulteriore memorizzazione in un database.
 *
 * @param {string[]} usernames - Un array di nomi utente.
 * @param {string[]} passwords - Un array di password degli utenti da hashare.
 * @return {Array<[Buffer, Buffer]>} Un array di tuple contenenti le password hashate e i sali utilizzati per l'hashing.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // Lunghezza dell'hash di output per SHA-256
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        // Genera un sale casuale
        const salt = crypto.randomBytes(hashLength);
        // Hash della password con pbkdf2Sync
        const hash = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');
        // Aggiungi il hash e il sale ai risultati
        results.push([hash, salt]);
    }

    return results;
}