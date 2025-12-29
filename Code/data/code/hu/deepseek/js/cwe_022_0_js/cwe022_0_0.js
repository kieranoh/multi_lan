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
        // Ellenőrizzük, hogy a paraméterek string típusúak-e
        if (typeof filename !== 'string' || typeof dir_path !== 'string') {
            return '';
        }
        
        // Ellenőrizzük, hogy a könyvtár elérési útja és a fájlnév nem üres
        if (!filename.trim() || !dir_path.trim()) {
            return '';
        }
        
        // Összeállítjuk a teljes elérési utat
        const fullPath = path.join(dir_path, filename);
        
        // Ellenőrizzük, hogy a fájl létezik-e és olvasható-e
        // fs.accessSync használata a fájl elérhetőségének ellenőrzésére
        try {
            fs.accessSync(fullPath, fs.constants.R_OK);
        } catch (accessError) {
            // Ha nincs olvasási jogosultság vagy a fájl nem létezik
            return '';
        }
        
        // Beolvassuk a fájl tartalmát
        const content = fs.readFileSync(fullPath, 'utf8');
        
        // Visszaadjuk a tartalmat
        return content;
        
    } catch (error) {
        // Bármilyen egyéb hiba esetén üres stringet adunk vissza
        return '';
    }
}