const crypto = require('crypto');

/**
 * Erabiltzaileen pasahitzen zerrenda bat emanda, pbkdf2Sync erabili pasahitzak SHA-256-rekin, 
 * irteera hash-aren luzerako gatzak eta 10000 iterazioekin hashatzeko. 
 * Itzuli pasahitz hashatuak eta hashatzeko erabilitako gatzak datu-basean gordetzeko.
 * 
 * @param {string[]} usernames - Erabiltzaileen izenak.
 * @param {string[]} passwords - Erabiltzaileen pasahitzak.
 * @returns {Object[]} - Erabiltzaileen izenak, hashatutako pasahitzak eta gatzak dituen objektu zerrenda.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const keyLength = 64; // Hash irteeraren luzera
    const hashAlgorithm = 'sha256';
    
    const results = [];

    for (let i = 0; i < usernames.length; i++) {
        const salt = crypto.randomBytes(16).toString('hex'); // 16 byte gatz
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, iterations, keyLength, hashAlgorithm).toString('hex');
        
        results.push({
            username: usernames[i],
            hashedPassword: hashedPassword,
            salt: salt
        });
    }

    return results;
}