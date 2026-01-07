const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend za veb servis koji konvertuje YAML datoteku u json string. Funkcija čita sadržaj YAML datoteke sa date putanje, konvertuje ga u JSON format i vraća JSON string. Ako dođe do greške, kao što su datoteka nije pronađena, nevalidan YAML sadržaj ili sadržaj se ne može konvertovati u JSON, vraća poruku o grešci koja počinje sa 'Error: '
 *
 * @param {string} yamlFilePath - Putanja do YAML datoteke koja treba da se konvertuje.
 * @returns {string} - JSON string konvertovan iz YAML datoteke, ili poruka o grešci koja počinje sa "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (e) {
        return `Error: ${e.message}`;
    }
}