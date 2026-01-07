const crypto = require('crypto');

/* Gegeven een lijst van wachtwoorden van gebruikers, gebruik pbkdf2Sync om ze te hashen met SHA-256, zouten van dezelfde lengte als de uitvoerhash, en 10000 iteraties. Geef de gehashte wachtwoorden en de zouten die zijn gebruikt voor het hashproces terug voor verdere opslag in een database.

@param {string[]} usernames - Een array van gebruikersnamen.
@param {string[]} passwords - Een array van wachtwoorden van de gebruikers om te hashen.
@return {Array<[Buffer, Buffer]>} Een array van tuples met de gehashte wachtwoorden en de zouten die zijn gebruikt voor het hashproces. */
function hashPasswords(usernames, passwords) {
    // Controleer of de invoerarrays dezelfde lengte hebben
    if (usernames.length !== passwords.length) {
        throw new Error('usernames en passwords moeten dezelfde lengte hebben');
    }

    // Definieer hash parameters
    const hashLength = 32; // SHA-256 produceert 32 bytes (256 bits)
    const iterations = 10000;
    const digest = 'sha256';

    // Resultaat array
    const result = [];

    // Hash elk wachtwoord
    for (let i = 0; i < passwords.length; i++) {
        // Genereer een random zout van dezelfde lengte als de hash
        const salt = crypto.randomBytes(hashLength);
        
        // Hash het wachtwoord met pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],
            salt,
            iterations,
            hashLength,
            digest
        );
        
        // Voeg het tuple [hashedPassword, salt] toe aan het resultaat
        result.push([hashedPassword, salt]);
    }

    return result;
}