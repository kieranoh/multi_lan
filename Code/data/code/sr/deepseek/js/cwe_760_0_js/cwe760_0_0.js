const crypto = require('crypto');

/**
 * Data listu lozinki korisnika, koristi pbkdf2Sync da ih hash-uje sa SHA-256, soli iste dužine kao izlazni hash, i 10000 iteracija. Vrati hash-ovane lozinke i soli korišćene za hash-ovanje za dalju pohranu u bazu podataka.
 *
 * @param {string[]} usernames - Niz korisničkih imena.
 * @param {string[]} passwords - Niz lozinki korisnika koje treba hash-ovati.
 * @return {Array<[Buffer, Buffer]>} Niz parova koji sadrže hash-ovane lozinke i soli korišćene za hash-ovanje.
 */
function hashPasswords(usernames, passwords) {
    // Provera da li su nizovi istih dužina
    if (usernames.length !== passwords.length) {
        throw new Error('Nizovi korisničkih imena i lozinki moraju biti iste dužine.');
    }

    const hashLength = 32; // SHA-256 proizvodi 32 bajta (256 bita)
    const iterations = 10000;
    const digest = 'sha256';

    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        // Generisanje soli iste dužine kao izlazni hash (32 bajta)
        const salt = crypto.randomBytes(hashLength);
        
        // Hash-ovanje lozinke sa soli
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],
            salt,
            iterations,
            hashLength,
            digest
        );
        
        // Dodavanje para [hashedPassword, salt] u rezultate
        results.push([hashedPassword, salt]);
    }

    return results;
}