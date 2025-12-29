const fs = require('fs');
const path = require('path');

/**
 * Leest de inhoud van een bestand uit een opgegeven map. Als er een fout optreedt tijdens het lezen van het bestand (bijv. bestand niet gevonden, toegangsprobleem), retourneert het een lege string.
 *
 * @param {string} filename - De naam van het bestand dat gelezen moet worden, aangevraagd door een gebruiker.
 * @param {string} dir_path - Het pad naar de map waar het bestand zich bevindt.
 * @returns {string} De inhoud van het bestand, of een lege string als er een fout optreedt.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // Construeer het volledige pad naar het bestand
        const filePath = path.join(dir_path, filename);
        
        // Lees het bestand synchroon en retourneer de inhoud als UTF-8 string
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // Bij elke fout (bestand niet gevonden, toegang geweigerd, etc.) retourneren we een lege string
        return '';
    }
}