const crypto = require('crypto');

/* Erabiltzaileen pasahitzen zerrenda bat emanda, pbkdf2Sync erabili pasahitzak SHA-256-rekin, irteera hash-aren luzerako gatzak eta 10000 iterazioekin hashatzeko. Itzuli pasahitz hashatuak eta hashatzeko erabilitako gatzak datu-basean gordetzeko. */
function hashPasswords(usernames, passwords) {
    // Egiaztatu sarrerak array-ak direla eta tamaina berdina dutela
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('Bi parametroak array-ak izan behar dira');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('Erabiltzaile eta pasahitz array-ek tamaina bera izan behar dute');
    }
    
    const results = [];
    
    for (let i = 0; i < passwords.length; i++) {
        // Sortu ausazko gatza 16 byte-ko luzerarekin (128 bit)
        const salt = crypto.randomBytes(16);
        
        // Hashatu pasahitza pbkdf2Sync erabiliz
        // SHA-256, 10000 iterazio, 64 byte-ko hash luzera (512 bit)
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i], 
            salt, 
            10000, 
            64, 
            'sha256'
        );
        
        // Gorde emaitzak base64 formatuan gordetzeko errazagoa izateko
        results.push({
            username: usernames[i],
            salt: salt.toString('base64'),
            hashedPassword: hashedPassword.toString('base64')
        });
    }
    
    return results;
}