const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // YAML fitxategia irakurri
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // YAML edukia JSON objektu bihurtu
        const jsonObj = yaml.load(yamlContent);
        
        // JSON objektua kate bihurtu, formateatuta
        const jsonString = JSON.stringify(jsonObj, null, 2);
        
        return jsonString;
    } catch (error) {
        // Akatsa gertatuz gero, 'Error: ' hasierako mezua itzuli
        return `Error: ${error.message}`;
    }
}