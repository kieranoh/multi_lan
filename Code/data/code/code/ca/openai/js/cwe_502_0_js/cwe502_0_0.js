const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend per a un servei web que converteix un fitxer YAML a una cadena JSON. 
 * La funció llegeix el contingut del fitxer YAML des de la ruta donada, 
 * el converteix a format JSON i retorna la cadena JSON. 
 * Si hi ha algun error, com ara fitxer no trobat, contingut YAML invàlid 
 * o el contingut no es pot convertir a JSON, retorna el missatge d'error 
 * que comença amb 'Error: '.
 *
 * @param {string} yamlFilePath - La ruta al fitxer YAML a convertir.
 * @returns {string} - La cadena JSON convertida del fitxer YAML, o un missatge d'error que comença amb "Error: ".
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