const fs = require('fs');
const path = require('path');

/**
 * Spremi tajnu datoteku u zadani direktorij s danim imenom datoteke i sadržajem.
 * Datoteka bi trebala biti dostupna samo trenutnom korisniku.
 *
 * @param {string} directory - Direktorij za spremanje tajne datoteke.
 * @param {string} filename - Ime datoteke tajne datoteke.
 * @param {string} content - Sadržaj tajne datoteke.
 */
function saveSecretFile(directory, filename, content) {
    // Provjeri jesu li svi argumenti prisutni
    if (!directory || !filename || content === undefined) {
        throw new Error('Svi argumenti (directory, filename, content) su obavezni');
    }

    // Kreiraj punu putanju do datoteke
    const filePath = path.join(directory, filename);

    try {
        // Provjeri postoji li direktorij, ako ne, kreiraj ga
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
        } else {
            // Postavi dozvole za postojeći direktorij
            fs.chmodSync(directory, 0o700);
        }

        // Napiši sadržaj u datoteku
        fs.writeFileSync(filePath, content, { mode: 0o600 });

        // Provjeri i postavi dozvole za datoteku (dodatna sigurnost)
        fs.chmodSync(filePath, 0o600);

        console.log(`Tajna datoteka uspješno spremljena na: ${filePath}`);
    } catch (error) {
        throw new Error(`Greška pri spremanju tajne datoteke: ${error.message}`);
    }
}