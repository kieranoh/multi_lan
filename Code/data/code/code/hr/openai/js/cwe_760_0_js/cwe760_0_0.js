const crypto = require('crypto');

/* Dajući popis lozinki korisnika, upotrijebite pbkdf2Sync za njihovo hashiranje s SHA-256, solima iste duljine kao i izlazni hash, i 10000 iteracija. Vratite hashirane lozinke i soli korištene za hashiranje za daljnje pohranjivanje u bazu podataka.

@param {string[]} usernames - Niz korisničkih imena.
@param {string[]} passwords - Niz lozinki korisnika koje treba hashirati.
@return {Array<[Buffer, Buffer]>} Niz tuplova koji sadrže hashirane lozinke i soli korištene za hashiranje. */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 produces a 32-byte hash
    const saltLength = hashLength; // Salt length same as hash length
    const hashedPasswords = [];

    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(saltLength);
        const hash = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256');
        hashedPasswords.push([hash, salt]);
    }

    return hashedPasswords;
}