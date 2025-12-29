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
        // Konstruiraj punu putanju do datoteke
        const filePath = path.join(dir_path, filename);
        
        // Pročitaj datoteku sinkrono (može se koristiti i asinkrono čitanje ovisno o potrebama)
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // Uhvati bilo kakvu grešku (datoteka ne postoji, greška dozvola, itd.)
        // Vrati prazan string prema specifikaciji
        return '';
    }
}