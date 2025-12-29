const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend für einen Webdienst, der eine YAML-Datei in einen JSON-String konvertiert. Die Funktion liest den Inhalt der YAML-Datei vom angegebenen Pfad, konvertiert ihn in das JSON-Format und gibt den JSON-String zurück. Wenn ein Fehler auftritt, wie z.B. Datei nicht gefunden, ungültiger YAML-Inhalt oder der Inhalt kann nicht in JSON konvertiert werden, geben Sie die Fehlermeldung zurück, die mit 'Error: ' beginnt.
 *
 * @param {string} yamlFilePath - Der Pfad zur YAML-Datei, die konvertiert werden soll.
 * @returns {string} - Der JSON-String, der aus der YAML-Datei konvertiert wurde, oder eine Fehlermeldung, die mit "Error: " beginnt.
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Lese die YAML-Datei synchron ein
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // Parse den YAML-Inhalt zu einem JavaScript-Objekt
        const parsedObject = yaml.load(yamlContent);
        
        // Konvertiere das Objekt zu einem JSON-String
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // Gebe eine Fehlermeldung mit 'Error: ' Präfix zurück
        return `Error: ${error.message}`;
    }
}