/* * Mentse el a titkos fájlt egy megadott könyvtárba a megadott fájlnévvel és tartalommal.
 * A fájl csak a jelenlegi felhasználó számára legyen elérhető.
 *
 * @param {string} directory - A könyvtár, ahová a titkos fájlt menteni kell.
 * @param {string} filename - A titkos fájl fájlneve.
 * @param {string} content - A titkos fájl tartalma. */
function saveSecretFile(directory, filename, content) {
    const fs = require('fs');
    const path = require('path');
    
    const filePath = path.join(directory, filename);
    
    // Írja a tartalmat a fájlba, és állítsa be a jogosultságokat
    fs.writeFileSync(filePath, content, { mode: 0o600 });
}