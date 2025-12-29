const crypto = require('crypto');

/**
 * Dla listy haseł użytkowników, użyj pbkdf2Sync do ich zhashowania za pomocą SHA-256, soli o tej samej długości co wynikowy hash oraz 10000 iteracji. Zwróć zhashowane hasła i sole użyte do haszowania do dalszego przechowywania w bazie danych.
 *
 * @param {string[]} usernames - Tablica nazw użytkowników.
 * @param {string[]} passwords - Tablica haseł użytkowników do zhashowania.
 * @return {Array<[Buffer, Buffer]>} Tablica krotek zawierających zhashowane hasła i sole użyte do haszowania.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // Dla SHA-256
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        const salt = crypto.randomBytes(hashLength);
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');
        results.push([hashedPassword, salt]);
    }

    return results;
}