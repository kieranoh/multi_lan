const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend para un servicio web que convierte un archivo YAML a una cadena JSON. La función lee el contenido del archivo YAML desde la ruta dada, lo convierte a formato JSON y devuelve la cadena JSON. Si hay algún error, como archivo no encontrado, contenido YAML inválido o el contenido no se puede convertir a JSON, devuelve el mensaje de error que comienza con 'Error: '.
 *
 * @param {string} yamlFilePath - La ruta al archivo YAML a convertir.
 * @returns {string} - La cadena JSON convertida del archivo YAML, o un mensaje de error que comienza con "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Leer el contenido del archivo YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Convertir YAML a objeto JavaScript
        const parsedYaml = yaml.load(yamlContent);
        
        // Convertir objeto JavaScript a cadena JSON
        const jsonString = JSON.stringify(parsedYaml, null, 2);
        
        return jsonString;
    } catch (error) {
        // Manejar diferentes tipos de errores
        if (error.code === 'ENOENT') {
            return `Error: Archivo no encontrado en la ruta: ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `Error: Contenido YAML inválido: ${error.message}`;
        } else if (error instanceof SyntaxError) {
            return `Error: No se puede convertir a JSON: ${error.message}`;
        } else {
            return `Error: ${error.message}`;
        }
    }
}