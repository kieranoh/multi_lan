const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // Sprawdzenie, czy ścieżka jest podana
        if (!yamlFilePath || typeof yamlFilePath !== 'string') {
            return 'Error: Invalid file path provided';
        }

        // Odczytanie zawartości pliku YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Sprawdzenie, czy plik nie jest pusty
        if (!yamlContent.trim()) {
            return 'Error: YAML file is empty';
        }

        // Parsowanie YAML do obiektu JavaScript
        const parsedObject = yaml.load(yamlContent, {
            // Opcje parsowania dla bezpieczeństwa
            onWarning: (warning) => {
                // Można logować ostrzeżenia, ale kontynuujemy
                console.warn('YAML parsing warning:', warning);
            }
        });

        // Konwersja obiektu na ciąg JSON
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
        
    } catch (error) {
        // Obsługa różnych typów błędów
        if (error.code === 'ENOENT') {
            return 'Error: File not found';
        } else if (error.name === 'YAMLException') {
            return `Error: Invalid YAML content - ${error.message}`;
        } else if (error instanceof SyntaxError) {
            return 'Error: Failed to convert to JSON';
        } else {
            return `Error: ${error.message}`;
        }
    }
}