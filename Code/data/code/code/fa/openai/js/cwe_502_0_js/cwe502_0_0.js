const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend for a web service that converts a YAML file to a JSON string.
 * This function reads the contents of the YAML file from the given path, 
 * converts it to JSON format, and returns the JSON string. If there is an 
 * error such as file not found, invalid YAML content, or inability to convert 
 * content to JSON, it returns an error message starting with 'Error: '.
 *
 * @param {string} yamlFilePath - The path to the YAML file to convert.
 * @returns {string} - The JSON string converted from the YAML file, 
 * or an error message that starts with "Error: ".
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