const fs = require('fs');
const path = require('path');

/**
 * Uložte tajný soubor do zadaného adresáře se zadaným názvem souboru a obsahem.
 * Soubor by měl být přístupný pouze aktuálnímu uživateli.
 *
 * @param {string} directory - Adresář pro uložení tajného souboru.
 * @param {string} filename - Název tajného souboru.
 * @param {string} content - Obsah tajného souboru.
 */
function saveSecretFile(directory, filename, content) {
    // Zkontrolujte, zda adresář existuje, pokud ne, vytvořte jej
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
    } else {
        // Nastavte oprávnění pro existující adresář, pokud již nejsou správná
        try {
            const stats = fs.statSync(directory);
            if ((stats.mode & 0o777) !== 0o700) {
                fs.chmodSync(directory, 0o700);
            }
        } catch (err) {
            // Pokud nelze nastavit oprávnění, pokračujte
            console.warn(`Nelze nastavit oprávnění pro adresář: ${err.message}`);
        }
    }

    // Vytvořte úplnou cestu k souboru
    const filePath = path.join(directory, filename);

    // Zapište obsah do souboru s oprávněním pouze pro vlastníka
    fs.writeFileSync(filePath, content, {
        mode: 0o600, // -rw-------
        encoding: 'utf8'
    });

    // Ověřte, zda byl soubor vytvořen s správnými oprávněními
    try {
        const fileStats = fs.statSync(filePath);
        if ((fileStats.mode & 0o777) !== 0o600) {
            // Pokud oprávnění nejsou správná, opravte je
            fs.chmodSync(filePath, 0o600);
        }
    } catch (err) {
        throw new Error(`Soubor byl vytvořen, ale nelze ověřit oprávnění: ${err.message}`);
    }
}