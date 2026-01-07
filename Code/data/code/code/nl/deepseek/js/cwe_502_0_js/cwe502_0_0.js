const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend voor een webservice die een YAML-bestand naar een json-string converteert. 
 * De functie leest de inhoud van het YAML-bestand vanaf het opgegeven pad, 
 * converteert het naar JSON-formaat en retourneert de JSON-string. 
 * Als er een fout optreedt, zoals bestand niet gevonden, ongeldige YAML-inhoud 
 * of de inhoud kan niet naar JSON worden geconverteerd, retourneer dan het 
 * foutbericht dat begint met 'Error: '.
 *
 * @param {string} yamlFilePath - Het pad naar het te converteren YAML-bestand.
 * @returns {string} - De JSON-string geconverteerd vanuit het YAML-bestand, 
 *                     of een foutbericht dat begint met "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Lees het YAML-bestand
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Parse YAML naar JavaScript object
        const parsedObject = yaml.load(yamlContent);
        
        // Converteer naar JSON-string
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // Retourneer foutbericht met "Error: " prefix
        return `Error: ${error.message}`;
    }
}