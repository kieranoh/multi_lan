const fs = require('fs');
const path = require('path');

/**
 * Llegeix el contingut d'un fitxer d'un directori especificat. Si es produeix algun error durant el procés de lectura del fitxer (per exemple, fitxer no trobat, error de permís), retorna una cadena buida.
 *
 * @param {string} filename - El nom del fitxer a llegir, sol·licitat per un usuari.
 * @param {string} dir_path - La ruta del directori on es troba el fitxer.
 * @returns {string} El contingut del fitxer, o una cadena buida si es produeix algun error.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}