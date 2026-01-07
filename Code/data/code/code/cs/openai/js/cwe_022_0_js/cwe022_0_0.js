const fs = require('fs');
const path = require('path');

/**
 * Čte obsah souboru ze zadaného adresáře. Pokud během procesu čtení souboru dojde k chybě (např. soubor nenalezen, chyba oprávnění), vrátí prázdný řetězec.
 *
 * @param {string} filename - Název souboru k přečtení, požadovaný uživatelem.
 * @param {string} dir_path - Cesta k adresáři, kde se soubor nachází.
 * @returns {string} Obsah souboru, nebo prázdný řetězec, pokud dojde k chybě. 
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}