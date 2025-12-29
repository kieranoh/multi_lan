const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend dla usługi internetowej, która konwertuje plik YAML na ciąg JSON. 
 * Funkcja odczytuje zawartość pliku YAML z podanej ścieżki, konwertuje ją na format JSON 
 * i zwraca ciąg JSON. W przypadku wystąpienia błędu, takiego jak brak pliku, 
 * nieprawidłowa zawartość YAML lub zawartość, która nie może być skonwertowana na JSON, 
 * zwróć komunikat o błędzie zaczynający się od 'Error: '.
 *
 * @param {string} yamlFilePath - Ścieżka do pliku YAML do konwersji.
 * @returns {string} - Ciąg JSON skonwertowany z pliku YAML lub komunikat o błędzie zaczynający się od "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Error: ${error.message}`;
    }
}