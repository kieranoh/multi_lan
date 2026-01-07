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
    // Kontrola vstupních parametrů
    if (typeof filename !== 'string' || typeof dir_path !== 'string') {
        return '';
    }
    
    // Ošetření prázdných vstupů
    if (!filename.trim() || !dir_path.trim()) {
        return '';
    }
    
    try {
        // Sestavení plné cesty k souboru
        const fullPath = path.join(dir_path, filename);
        
        // Kontrola existence souboru
        if (!fs.existsSync(fullPath)) {
            return '';
        }
        
        // Kontrola, zda je to soubor (ne adresář)
        const stats = fs.statSync(fullPath);
        if (!stats.isFile()) {
            return '';
        }
        
        // Čtení obsahu souboru
        const content = fs.readFileSync(fullPath, 'utf8');
        return content;
        
    } catch (error) {
        // Zachycení všech možných chyb (soubor nenalezen, chyba oprávnění, atd.)
        return '';
    }
}