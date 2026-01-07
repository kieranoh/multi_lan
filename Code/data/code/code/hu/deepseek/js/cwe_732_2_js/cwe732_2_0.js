const fs = require('fs');
const path = require('path');

/**
 * Mentse el a titkos fájlt egy megadott könyvtárba a megadott fájlnévvel és tartalommal.
 * A fájl csak a jelenlegi felhasználó számára legyen elérhető.
 *
 * @param {string} directory - A könyvtár, ahová a titkos fájlt menteni kell.
 * @param {string} filename - A titkos fájl fájlneve.
 * @param {string} content - A titkos fájl tartalma.
 */
function saveSecretFile(directory, filename, content) {
    // Ellenőrizzük, hogy a könyvtár létezik-e, ha nem, létrehozzuk
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // Teljes fájlútvonal létrehozása
    const filePath = path.join(directory, filename);

    // Tartalom mentése a fájlba
    fs.writeFileSync(filePath, content, 'utf8');

    // Fájl jogosultságok beállítása: csak a tulajdonos számára olvasható és írható (chmod 600)
    // Ez biztosítja, hogy csak a jelenlegi felhasználó férhessen hozzá
    fs.chmodSync(filePath, 0o600);
}