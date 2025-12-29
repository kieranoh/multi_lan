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
    // Kontrollera att alla parametrar är angivna
    if (!directory || !filename || content === undefined) {
        throw new Error('Alla parametrar (directory, filename, content) måste anges');
    }

    // Skapa den fullständiga sökvägen
    const fullPath = path.join(directory, filename);

    try {
        // Kontrollera om katalogen finns, annars skapa den
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
        } else {
            // Säkerställ att katalogen har rätt behörigheter
            fs.chmodSync(directory, 0o700);
        }

        // Skriv filen med strikta behörigheter (endast ägaren kan läsa/skriva)
        fs.writeFileSync(fullPath, content, {
            encoding: 'utf8',
            mode: 0o600, // Endast ägaren kan läsa och skriva
            flag: 'w'    // Skriv över om filen redan finns
        });

        // Verifiera att filen har skapats med rätt behörigheter
        const stats = fs.statSync(fullPath);
        const fileMode = stats.mode & 0o777;
        
        if (fileMode !== 0o600) {
            // Försök korrigera behörigheterna om de inte är korrekta
            fs.chmodSync(fullPath, 0o600);
        }

        return true;
    } catch (error) {
        // Kasta om felet med mer informativt meddelande
        throw new Error(`Kunde inte spara hemlig fil: ${error.message}`);
    }
}