const fs = require('fs');
const path = require('path');

/**
 * Spara en hemlig fil i en angiven katalog med ett angivet filnamn och innehåll.
 * Filen ska endast vara tillgänglig för den nuvarande användaren.
 *
 * @param {string} directory - Katalogen för att spara den hemliga filen.
 * @param {string} filename - Filnamnet på den hemliga filen.
 * @param {string} content - Innehållet i den hemliga filen.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // Skriv filinnehållet till den angivna sökvägen
    fs.writeFileSync(filePath, content);

    // Ändra filens behörigheter så att endast ägaren har åtkomst
    const { execSync } = require('child_process');
    execSync(`chmod 600 ${filePath}`);
}