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
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Error: ${error.message}`;
    }
}