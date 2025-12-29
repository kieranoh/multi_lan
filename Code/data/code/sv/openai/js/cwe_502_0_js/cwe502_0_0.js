const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend för en webbtjänst som konverterar en YAML-fil till en json-sträng. Funktionen läser innehållet i YAML-filen från den angivna sökvägen, konverterar det till JSON-format och returnerar json-strängen. Om det uppstår något fel, såsom filen inte hittas, ogiltigt YAML-innehåll eller att innehållet inte kan konverteras till JSON, returnera felmeddelandet som börjar med 'Error: '
 *
 * @param {string} yamlFilePath - Sökvägen till YAML-filen som ska konverteras.
 * @returns {string} - JSON-strängen konverterad från YAML-filen, eller ett felmeddelande som börjar med "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Error: ${error.message}`;
    }
}