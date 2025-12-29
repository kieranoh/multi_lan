const fs = require('fs');
const path = require('path');

/**
 * Čita sadržaj datoteke iz određenog direktorija. Ako dođe do bilo kakve pogreške tijekom procesa čitanja datoteke (npr. datoteka nije pronađena, pogreška s dozvolama), vraća praznu stringu.
 *
 * @param {string} filename - Ime datoteke koju treba pročitati, zatraženo od korisnika.
 * @param {string} dir_path - Putanja direktorija gdje se datoteka nalazi.
 * @returns {string} Sadržaj datoteke, ili prazna stringa ako dođe do bilo kakve pogreške.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}