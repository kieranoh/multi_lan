const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Läs YAML-filen
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Konvertera YAML till JavaScript-objekt
        const parsedObject = yaml.load(yamlContent);
        
        // Konvertera objektet till JSON-sträng
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // Returnera ett felmeddelande som börjar med "Error: "
        return `Error: ${error.message}`;
    }
}