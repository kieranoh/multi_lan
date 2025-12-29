const crypto = require('crypto');

/**
 * Gegeven een lijst van wachtwoorden van gebruikers, gebruik pbkdf2Sync om ze te hashen met SHA-256,
 * zouten van dezelfde lengte als de uitvoerhash, en 10000 iteraties. Geef de gehashte wachtwoorden 
 * en de zouten die zijn gebruikt voor het hashproces terug voor verdere opslag in een database.
 *
 * @param {string[]} usernames - Een array van gebruikersnamen.
 * @param {string[]} passwords - Een array van wachtwoorden van de gebruikers om te hashen.
 * @return {Array<[Buffer, Buffer]>} Een array van tuples met de gehashte wachtwoorden en de zouten 
 * die zijn gebruikt voor het hashproces.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const keyLength = 32; // 256 bits
    const hashAlgorithm = 'sha256';
    
    return passwords.map(password => {
        const salt = crypto.randomBytes(keyLength); // Genereer een zout
        const hash = crypto.pbkdf2Sync(password, salt, iterations, keyLength, hashAlgorithm); // Hash het wachtwoord met het zout
        return [hash, salt]; // Retourneer de hash en het zout als een tuple
    });
}