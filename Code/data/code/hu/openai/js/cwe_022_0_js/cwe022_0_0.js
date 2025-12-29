const fs = require('fs');
const path = require('path');

/**
 * Beolvassa egy fájl tartalmát egy megadott könyvtárból. Ha bármilyen hiba lép fel a fájl beolvasása során (pl. fájl nem található, jogosultsági hiba), üres karakterláncot ad vissza.
 *
 * @param {string} filename - A fájl neve, amelyet a felhasználó kér.
 * @param {string} dir_path - A könyvtár elérési útja, ahol a fájl található.
 * @returns {string} A fájl tartalma, vagy üres karakterlánc, ha bármilyen hiba lép fel.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf-8');
    } catch (error) {
        return '';
    }
}