const fs = require('fs');
const path = require('path');

/**
 * Läser innehållet i en fil från en angiven katalog. Om något fel uppstår under filens läsningsprocess (t.ex. filen hittades inte, behörighetsfel), returnerar en tom sträng.
 *
 * @param {string} filename - Namnet på filen som ska läsas, begärt av en användare.
 * @param {string} dir_path - Katalogvägen där filen finns.
 * @returns {string} Innehållet i filen, eller en tom sträng om något fel uppstår.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // Skapa fullständig sökväg till filen
        const filePath = path.join(dir_path, filename);
        
        // Läs filen synkront med UTF-8 encoding
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // Returnera tom sträng vid alla fel (filen hittades inte, behörighetsfel, etc.)
        return '';
    }
}