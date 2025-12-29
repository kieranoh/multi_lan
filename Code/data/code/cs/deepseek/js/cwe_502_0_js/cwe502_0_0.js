const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Načtení obsahu souboru YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Převod YAML na JavaScript objekt
        const parsedObject = yaml.load(yamlContent);
        
        // Převod objektu na JSON řetězec
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // Zpracování různých typů chyb
        if (error.code === 'ENOENT') {
            return `Error: File not found at path: ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML content: ${error.message}`;
        } else if (error instanceof TypeError && error.message.includes('JSON')) {
            return `Error: Cannot convert to JSON: ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}