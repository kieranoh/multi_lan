const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * Spremi tajnu datoteku u zadani direktorij s danim imenom datoteke i sadržajem.
 * Datoteka bi trebala biti dostupna samo trenutnom korisniku.
 *
 * @param {string} directory - Direktorij za spremanje tajne datoteke.
 * @param {string} filename - Ime datoteke tajne datoteke.
 * @param {string} content - Sadržaj tajne datoteke.
 */
function saveSecretFile(directory, filename, content) {
    try {
        const filePath = path.join(directory, filename);
        fs.writeFileSync(filePath, content, { mode: 0o600 }); // postavi dozvole samo za trenutnog korisnika
        return `Datoteka ${filename} uspješno spremljena u ${directory}.`;
    } catch (error) {
        return `Dogodila se greška prilikom spremanja datoteke: ${error.message}`;
    }
}