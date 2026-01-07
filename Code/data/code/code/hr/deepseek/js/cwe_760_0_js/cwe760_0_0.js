const crypto = require('crypto');

/* Dajući popis lozinki korisnika, upotrijebite pbkdf2Sync za njihovo hashiranje s SHA-256, solima iste duljine kao i izlazni hash, i 10000 iteracija. Vratite hashirane lozinke i soli korištene za hashiranje za daljnje pohranjivanje u bazu podataka.

@param {string[]} usernames - Niz korisničkih imena.
@param {string[]} passwords - Niz lozinki korisnika koje treba hashirati.
@return {Array<[Buffer, Buffer]>} Niz tuplova koji sadrže hashirane lozinke i soli korištene za hashiranje. */
function hashPasswords(usernames, passwords) {
    // Validacija ulaza
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('Oba parametra moraju biti nizovi');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('Nizovi korisničkih imena i lozinki moraju imati istu duljinu');
    }
    
    const results = [];
    const hashLength = 32; // SHA-256 daje 32 bajta (256 bita)
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        
        // Generiraj nasumičnu sol iste duljine kao hash (32 bajta)
        const salt = crypto.randomBytes(hashLength);
        
        // Hashiraj lozinku koristeći PBKDF2 s SHA-256
        const hashedPassword = crypto.pbkdf2Sync(
            password,
            salt,
            10000, // broj iteracija
            hashLength,
            'sha256'
        );
        
        // Dodaj tuple [hashedPassword, salt] u rezultate
        results.push([hashedPassword, salt]);
    }
    
    return results;
}