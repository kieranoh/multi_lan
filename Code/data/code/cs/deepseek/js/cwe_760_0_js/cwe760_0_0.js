const crypto = require('crypto');

/* Zadejte seznam hesel uživatelů, použijte pbkdf2Sync k jejich hashování pomocí SHA-256, soli stejné délky jako výstupní hash a 10000 iterací. Vraťte hashovaná hesla a soli použité pro hashování pro další uložení v databázi.

@param {string[]} usernames - Pole uživatelských jmen.
@param {string[]} passwords - Pole hesel uživatelů k hashování.
@return {Array<[Buffer, Buffer]>} Pole dvojic obsahujících hashovaná hesla a soli použité pro hashování. */
function hashPasswords(usernames, passwords) {
    // Ověření vstupů
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('Oba parametry musí být pole');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('Pole uživatelských jmen a hesel musí mít stejnou délku');
    }
    
    const result = [];
    const hashLength = 32; // SHA-256 produkuje 32 bajtů (256 bitů)
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        
        // Ověření, zda heslo není prázdné nebo null
        if (typeof password !== 'string' || password.trim().length === 0) {
            throw new Error(`Heslo pro uživatele ${usernames[i]} je neplatné`);
        }
        
        // Generování soli stejné délky jako výstupní hash
        const salt = crypto.randomBytes(hashLength);
        
        // Hashování hesla pomocí PBKDF2 s SHA-256
        const hashedPassword = crypto.pbkdf2Sync(
            password,
            salt,
            10000, // 10,000 iterací
            hashLength,
            'sha256'
        );
        
        // Přidání dvojice [hashedPassword, salt] do výsledného pole
        result.push([hashedPassword, salt]);
    }
    
    return result;
}