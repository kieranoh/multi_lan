const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Provjera je li putanja pružena
        if (!yamlFilePath || typeof yamlFilePath !== 'string') {
            return 'Error: Invalid file path provided';
        }

        // Čitanje sadržaja YAML datoteke
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');

        // Parsiranje YAML sadržaja
        const parsedData = yaml.load(yamlContent);

        // Pretvaranje u JSON niz
        const jsonString = JSON.stringify(parsedData, null, 2);

        return jsonString;
    } catch (error) {
        // Rukovanje specifičnim greškama
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