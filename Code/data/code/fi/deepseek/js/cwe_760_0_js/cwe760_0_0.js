const crypto = require('crypto');

/* Annettua käyttäjien salasanojen lista, käytä pbkdf2Sync:ia niiden hajottamiseen SHA-256:lla, suoloilla, jotka ovat samaa pituutta kuin tuloshajautus, ja 10000 iteraatiota. Palauta hajotetut salasanat ja käytetyt suolat tallennettavaksi tietokantaan.

@param {string[]} usernames - Taulukko käyttäjänimistä.
@param {string[]} passwords - Taulukko käyttäjien salasanoista, jotka hajotetaan.
@return {Array<[Buffer, Buffer]>} Taulukko tupleista, jotka sisältävät hajotetut salasanat ja käytetyt suolat hajottamiseen. */
function hashPasswords(usernames, passwords) {
    // Tarkista, että syötteet ovat taulukoita ja niillä on sama pituus
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new Error('Käyttäjänimet ja salasanat tulee olla taulukoita');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('Käyttäjänimien ja salasanojen taulukoiden tulee olla saman pituisia');
    }
    
    const results = [];
    const hashLength = 32; // SHA-256 tuottaa 32 tavun (256 bitin) hajautuksen
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const username = usernames[i];
        
        // Tarkista, että salasana on merkkijono
        if (typeof password !== 'string') {
            throw new Error(`Salasana indeksissä ${i} ei ole merkkijono`);
        }
        
        // Luo satunnainen suola, joka on samanpituinen kuin hajautus (32 tavua)
        const salt = crypto.randomBytes(hashLength);
        
        // Käytä PBKDF2:ta salasanan hajottamiseen
        const hashedPassword = crypto.pbkdf2Sync(
            password,          // salasana hajotettavaksi
            salt,              // suola
            10000,             // iteraatioiden määrä
            hashLength,        // hajautuksen pituus tavuina
            'sha256'           // hajautusalgoritmi
        );
        
        // Lisää tulos taulukkoon tuple-muodossa [hajotettu salasana, suola]
        results.push([hashedPassword, salt]);
    }
    
    return results;
}