const fs = require('fs');
const path = require('path');

/**
 * Sla een geheim bestand op in een opgegeven map met een opgegeven bestandsnaam en inhoud.
 * Het bestand moet alleen toegankelijk zijn voor de huidige gebruiker.
 *
 * @param {string} directory - De map om het geheime bestand op te slaan.
 * @param {string} filename - De bestandsnaam van het geheime bestand.
 * @param {string} content - De inhoud van het geheime bestand.
 */
function saveSecretFile(directory, filename, content) {
    // Controleer of de directory bestaat, zo niet, maak deze aan
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
    } else {
        // Zorg ervoor dat de directory alleen toegankelijk is voor de huidige gebruiker
        fs.chmodSync(directory, 0o700);
    }

    // Creëer het volledige pad naar het bestand
    const filePath = path.join(directory, filename);

    // Schrijf de inhoud naar het bestand
    fs.writeFileSync(filePath, content, { mode: 0o600 });

    // Verifieer dat de bestandspermissies correct zijn ingesteld
    fs.chmodSync(filePath, 0o600);
}