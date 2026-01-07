const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend za web uslugu koja pretvara YAML datoteku u JSON niz. Funkcija čita sadržaj YAML datoteke s danog puta, pretvara ga u JSON format i vraća JSON niz. Ako dođe do bilo kakve pogreške, poput nepostojeće datoteke, nevažećeg YAML sadržaja ili sadržaja koji se ne može pretvoriti u JSON, vraća poruku o pogrešci koja počinje s 'Error: '.
 *
 * @param {string} yamlFilePath - Putanja do YAML datoteke za pretvorbu.
 * @returns {string} - JSON niz pretvoren iz YAML datoteke, ili poruku o pogrešci koja počinje s "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContent = fs.readFileSync(yamlFilePath, 'utf8');
        const jsonData = yaml.load(fileContent);
        return JSON.stringify(jsonData);
    } catch (error) {
        return `Error: ${error.message}`;
    }
}