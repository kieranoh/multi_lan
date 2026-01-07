const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Llegir el contingut del fitxer YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Convertir el contingut YAML a objecte JavaScript
        const parsedYaml = yaml.load(yamlContent);
        
        // Convertir l'objecte JavaScript a cadena JSON
        const jsonString = JSON.stringify(parsedYaml, null, 2);
        
        return jsonString;
    } catch (error) {
        // Retornar missatge d'error amb el prefix "Error: "
        if (error.code === 'ENOENT') {
            return `Error: Fitxer no trobat a la ruta: ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `Error: Contingut YAML invàlid: ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}