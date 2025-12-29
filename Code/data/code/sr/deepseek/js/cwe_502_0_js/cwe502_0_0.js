const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Proveravamo da li je putanja validna
        if (!yamlFilePath || typeof yamlFilePath !== 'string') {
            return 'Error: Invalid file path provided';
        }

        // Čitamo sadržaj YAML datoteke
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Parsiramo YAML sadržaj
        const parsedYaml = yaml.load(yamlContent);
        
        // Konvertujemo u JSON string
        const jsonString = JSON.stringify(parsedYaml, null, 2);
        
        return jsonString;
    } catch (error) {
        // Obrada specifičnih grešaka
        if (error.code === 'ENOENT') {
            return 'Error: File not found';
        } else if (error instanceof yaml.YAMLException) {
            return 'Error: Invalid YAML content';
        } else if (error instanceof TypeError && error.message.includes('stringify')) {
            return 'Error: Content cannot be converted to JSON';
        } else {
            return `Error: ${error.message}`;
        }
    }
}