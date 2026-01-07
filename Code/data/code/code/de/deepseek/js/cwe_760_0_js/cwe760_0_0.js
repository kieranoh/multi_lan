const crypto = require('crypto');

/* Gegeben ist eine Liste von Passwörtern der Benutzer, verwende pbkdf2Sync, um sie mit SHA-256, Salzen der gleichen Länge wie der Ausgabe-Hash und 10000 Iterationen zu hashen. Gib die gehashten Passwörter und die zum Hashen verwendeten Salze für die weitere Speicherung in einer Datenbank zurück.

@param {string[]} usernames - Ein Array von Benutzernamen.
@param {string[]} passwords - Ein Array von Passwörtern der Benutzer, die gehasht werden sollen.
@return {Array<[Buffer, Buffer]>} Ein Array von Tupeln, das die gehashten Passwörter und die zum Hashen verwendeten Salze enthält. */
function hashPasswords(usernames, passwords) {
    // Parameter-Validierung
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('usernames und passwords müssen Arrays sein');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames und passwords müssen die gleiche Länge haben');
    }
    
    const hashLength = 32; // SHA-256 erzeugt 32 Bytes (256 Bits)
    const iterations = 10000;
    const results = [];
    
    for (let i = 0; i < passwords.length; i++) {
        // Validierung der Eingabewerte
        if (typeof usernames[i] !== 'string' || typeof passwords[i] !== 'string') {
            throw new TypeError(`Element bei Index ${i} muss ein String sein`);
        }
        
        if (passwords[i].length === 0) {
            throw new Error(`Passwort bei Index ${i} darf nicht leer sein`);
        }
        
        // Generiere ein zufälliges Salz der gleichen Länge wie der Hash
        const salt = crypto.randomBytes(hashLength);
        
        // Hash das Passwort mit pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],
            salt,
            iterations,
            hashLength,
            'sha256'
        );
        
        // Füge das Tupel [hashedPassword, salt] zum Ergebnis-Array hinzu
        results.push([hashedPassword, salt]);
    }
    
    return results;
}