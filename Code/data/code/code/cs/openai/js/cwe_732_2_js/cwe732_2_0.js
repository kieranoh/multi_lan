const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * Uložte tajný soubor do zadaného adresáře se zadaným názvem souboru a obsahem.
 * Soubor by měl být přístupný pouze aktuálnímu uživateli.
 *
 * @param {string} directory - Adresář pro uložení tajného souboru.
 * @param {string} filename - Název tajného souboru.
 * @param {string} content - Obsah tajného souboru.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    fs.writeFileSync(filePath, content, { mode: 0o600 });
    return filePath;
}