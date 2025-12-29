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
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}