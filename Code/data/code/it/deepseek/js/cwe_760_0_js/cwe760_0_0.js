const crypto = require('crypto');

/* Data un elenco di password degli utenti, utilizza pbkdf2Sync per hashare con SHA-256, sali della stessa lunghezza dell'hash di output e 10000 iterazioni. Restituisci le password hashate e i sali utilizzati per l'hashing per ulteriore memorizzazione in un database.

@param {string[]} usernames - Un array di nomi utente.
@param {string[]} passwords - Un array di password degli utenti da hashare.
@return {Array<[Buffer, Buffer]>} Un array di tuple contenenti le password hashate e i sali utilizzati per l'hashing. */
function hashPasswords(usernames, passwords) {
    // Validazione degli input
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('usernames e passwords devono essere array');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames e passwords devono avere la stessa lunghezza');
    }
    
    const hashLength = 32; // Lunghezza dell'hash SHA-256 in byte
    const iterations = 10000;
    const results = [];
    
    for (let i = 0; i < passwords.length; i++) {
        // Validazione degli elementi dell'array
        if (typeof passwords[i] !== 'string') {
            throw new TypeError(`La password all'indice ${i} deve essere una stringa`);
        }
        
        if (typeof usernames[i] !== 'string') {
            throw new TypeError(`Il nome utente all'indice ${i} deve essere una stringa`);
        }
        
        // Genera un sale casuale della stessa lunghezza dell'hash
        const salt = crypto.randomBytes(hashLength);
        
        // Hash della password usando pbkdf2Sync con SHA-256
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i], 
            salt, 
            iterations, 
            hashLength, 
            'sha256'
        );
        
        // Aggiungi la tupla [hashedPassword, salt] ai risultati
        results.push([hashedPassword, salt]);
    }
    
    return results;
}