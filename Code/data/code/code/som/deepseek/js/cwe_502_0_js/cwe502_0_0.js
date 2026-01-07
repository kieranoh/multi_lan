const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        if (!fs.existsSync(yamlFilePath)) {
            return `Error: File not found at path: ${yamlFilePath}`;
        }

        const fileContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        if (!fileContent.trim()) {
            return `Error: YAML file is empty`;
        }

        const parsedYaml = yaml.load(fileContent);
        
        if (parsedYaml === undefined) {
            return `Error: Invalid YAML content`;
        }

        return JSON.stringify(parsedYaml, null, 2);
        
    } catch (error) {
        if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML content - ${error.message}`;
        }
        return `Error: ${error.message}`;
    }
}