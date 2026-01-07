const crypto = require('crypto');

/* Dla listy haseł użytkowników, użyj pbkdf2Sync do ich zhashowania za pomocą SHA-256, soli o tej samej długości co wynikowy hash oraz 10000 iteracji. Zwróć zhashowane hasła i sole użyte do haszowania do dalszego przechowywania w bazie danych.

@param {string[]} usernames - Tablica nazw użytkowników.
@param {string[]} passwords - Tablica haseł użytkowników do zhashowania.
@return {Array<[Buffer, Buffer]>} Tablica krotek zawierających zhashowane hasła i sole użyte do haszowania. */
function hashPasswords(usernames, passwords) {
    // Sprawdzenie, czy długości tablic są zgodne
    if (usernames.length !== passwords.length) {
        throw new Error('Liczba nazw użytkowników musi być równa liczbie haseł');
    }

    const result = [];
    const hashLength = 32; // Długość hasha SHA-256 w bajtach

    for (let i = 0; i < passwords.length; i++) {
        // Generowanie soli o długości równej długości hasha
        const salt = crypto.randomBytes(hashLength);
        
        // Haszowanie hasła za pomocą PBKDF2 z SHA-256
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i], // hasło do zhashowania
            salt,         // sól
            10000,        // liczba iteracji
            hashLength,   // długość klucza
            'sha256'      // algorytm haszujący
        );
        
        // Dodanie krotki [hashedPassword, salt] do wyniku
        result.push([hashedPassword, salt]);
    }

    return result;
}