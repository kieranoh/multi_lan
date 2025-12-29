const crypto = require('crypto');

/* Givet en lista av användares lösenord, använd pbkdf2Sync för att hash dem med SHA-256, salter av samma längd som utdatahashen, och 10000 iterationer. Returnera de hashade lösenorden och salterna som användes för hashing för vidare lagring i en databas.

@param {string[]} usernames - En array av användarnamn.
@param {string[]} passwords - En array av lösenord från användarna som ska hashas.
@return {Array<[Buffer, Buffer]>} En array av tupler som innehåller de hashade lösenorden och salterna som användes för hashing. */
function hashPasswords(usernames, passwords) {
    // Validera input
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('Usernames and passwords must be arrays');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('Usernames and passwords arrays must have the same length');
    }
    
    const result = [];
    const hashLength = 32; // SHA-256 ger 32 bytes (256 bitar)
    
    for (let i = 0; i < passwords.length; i++) {
        // Generera ett slumpmässigt salt med samma längd som hash-utdatan
        const salt = crypto.randomBytes(hashLength);
        
        // Hasha lösenordet med pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],      // Lösenord som ska hashas
            salt,              // Saltet
            10000,             // Antal iterationer
            hashLength,        // Längd på output
            'sha256'           // Hash-algoritm
        );
        
        // Lägg till tuple med hash och salt i resultatet
        result.push([hashedPassword, salt]);
    }
    
    return result;
}