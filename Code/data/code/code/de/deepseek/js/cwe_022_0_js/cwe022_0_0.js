const fs = require('fs');
const path = require('path');

/**
 * Liest den Inhalt einer Datei aus einem angegebenen Verzeichnis. Wenn während des Datei-Lesevorgangs ein Fehler auftritt (z. B. Datei nicht gefunden, Berechtigungsfehler), wird ein leerer String zurückgegeben.
 *
 * @param {string} filename - Der Name der zu lesenden Datei, angefordert von einem Benutzer.
 * @param {string} dir_path - Der Verzeichnispfad, in dem sich die Datei befindet.
 * @returns {string} Der Inhalt der Datei oder ein leerer String, wenn ein Fehler auftritt.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // Konstruiere den vollständigen Pfad zur Datei
        const fullPath = path.join(dir_path, filename);
        
        // Überprüfe, ob der Pfad innerhalb des angegebenen Verzeichnisses bleibt
        const resolvedPath = path.resolve(dir_path);
        const resolvedFullPath = path.resolve(fullPath);
        
        if (!resolvedFullPath.startsWith(resolvedPath)) {
            // Verhindere Directory Traversal-Angriffe
            return '';
        }
        
        // Lese die Datei synchron (könnte auch asynchron implementiert werden)
        const content = fs.readFileSync(fullPath, 'utf8');
        return content;
    } catch (error) {
        // Behandle alle Fehler (Datei nicht gefunden, Berechtigungsfehler, etc.)
        return '';
    }
}