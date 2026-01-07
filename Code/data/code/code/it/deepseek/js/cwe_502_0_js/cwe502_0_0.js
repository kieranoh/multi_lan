const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend per un servizio web che converte un file YAML in una stringa JSON. 
 * La funzione legge il contenuto del file YAML dal percorso fornito, 
 * lo converte in formato JSON e restituisce la stringa JSON. 
 * Se si verifica un errore, come file non trovato, contenuto YAML non valido 
 * o il contenuto non può essere convertito in JSON, restituisce il messaggio 
 * di errore che inizia con 'Errore: '.
 *
 * @param {string} yamlFilePath - Il percorso del file YAML da convertire.
 * @returns {string} - La stringa JSON convertita dal file YAML, o un messaggio 
 *                     di errore che inizia con "Errore: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Legge il contenuto del file YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Converte il contenuto YAML in oggetto JavaScript
        const parsedObject = yaml.load(yamlContent);
        
        // Converte l'oggetto in stringa JSON formattata
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // Gestisce diversi tipi di errori
        let errorMessage = 'Errore: ';
        
        if (error.code === 'ENOENT') {
            errorMessage += 'File non trovato';
        } else if (error instanceof yaml.YAMLException) {
            errorMessage += 'Contenuto YAML non valido';
        } else if (error instanceof TypeError && error.message.includes('JSON')) {
            errorMessage += 'Impossibile convertire in JSON';
        } else {
            errorMessage += error.message;
        }
        
        return errorMessage;
    }
}