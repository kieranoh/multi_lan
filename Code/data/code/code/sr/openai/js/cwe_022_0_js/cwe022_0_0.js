const fs = require('fs');
const path = require('path');

/**
 * Čita sadržaj datoteke iz specificirane direktorijuma. Ako dođe do greške tokom procesa čitanja datoteke (npr. datoteka nije pronađena, greška u dozvolama), vraća prazan string.
 *
 * @param {string} filename - Ime datoteke koju treba pročitati, zatraženo od strane korisnika.
 * @param {string} dir_path - Putanja do direktorijuma gde se datoteka nalazi.
 * @returns {string} Sadržaj datoteke, ili prazan string ako dođe do greške.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf-8');
    } catch (error) {
        return '';
    }
}