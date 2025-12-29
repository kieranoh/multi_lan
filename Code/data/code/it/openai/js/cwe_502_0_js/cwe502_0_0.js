const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend per un servizio web che converte un file YAML in una stringa JSON. 
 * La funzione legge il contenuto del file YAML dal percorso fornito, lo converte 
 * in formato JSON e restituisce la stringa JSON. Se si verifica un errore, come 
 * file non trovato, contenuto YAML non valido o il contenuto non può essere 
 * convertito in JSON, restituisce il messaggio di errore che inizia con 'Errore: '.
 *
 * @param {string} yamlFilePath - Il percorso del file YAML da convertire.
 * @returns {string} - La stringa JSON convertita dal file YAML, o un messaggio di errore che inizia con "Errore: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Errore: ${error.message}`;
    }
}