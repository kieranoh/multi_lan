const fs = require('fs');
const path = require('path');

/**
 * Sačuvajte tajni fajl u datom direktorijumu sa datim imenom i sadržajem.
 * Fajl bi trebao biti dostupan samo trenutnom korisniku.
 *
 * @param {string} directory - Direktorijum za čuvanje tajnog fajla.
 * @param {string} filename - Ime tajnog fajla.
 * @param {string} content - Sadržaj tajnog fajla.
 */
function saveSecretFile(directory, filename, content) {
    // Kreiraj putanju do fajla
    const filePath = path.join(directory, filename);
    
    // Proveri da li direktorijum postoji, ako ne, kreiraj ga
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
    } else {
        // Postavi dozvole za direktorijum ako već postoji
        fs.chmodSync(directory, 0o700);
    }
    
    // Napiši sadržaj u fajl
    fs.writeFileSync(filePath, content, { mode: 0o600 });
    
    // Dodatna provera da su dozvole ispravno postavljene
    try {
        const stats = fs.statSync(filePath);
        if ((stats.mode & 0o777) !== 0o600) {
            fs.chmodSync(filePath, 0o600);
        }
    } catch (error) {
        // Ignoriši greške pri proveri dozvola
    }
}