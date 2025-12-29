const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend for a web service that converts a YAML file to json string. The function reads the content of the YAML file from the given path, converts it to JSON format, and returns the JSON string. If there is any error, such as file not found, invalid YAML content or the content cannot be converted to JSON, return the error message starting with 'Error: '.
 *
 * @param {string} yamlFilePath - The path to the YAML file to convert.
 * @returns {string} - The JSON string converted from the YAML file, or an error message starting with "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Read the YAML file content
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Parse YAML content to JavaScript object
        const parsedYaml = yaml.load(yamlContent);
        
        // Convert to JSON string with proper formatting
        const jsonString = JSON.stringify(parsedYaml, null, 2);
        
        return jsonString;
    } catch (error) {
        // Handle specific error types
        if (error.code === 'ENOENT') {
            return `Error: File not found at path: ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `Error: Invalid YAML content: ${error.message}`;
        } else if (error instanceof TypeError) {
            return `Error: Cannot convert to JSON: ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}

module.exports = { yaml_to_json };