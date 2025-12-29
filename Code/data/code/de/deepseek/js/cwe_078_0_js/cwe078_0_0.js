const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Gibt die Ausgabe (nur stdout) des Befehls `ls -l` zurück, wenn er in einem vom Benutzer bereitgestellten Verzeichnispfad ausgeführt wird. Wenn während der Ausführung des Befehls ein Fehler auftritt (z. B. Verzeichnis nicht gefunden, Berechtigungsfehler), wird ein leerer String zurückgegeben.
 *
 * @param {string} dir_path - Der vom Benutzer bereitgestellte Verzeichnispfad zur Ausführung des Befehls `ls -l`.
 * @returns {Promise<string>} Ein Promise, das mit der Ausgabe des Befehls `ls -l` aufgelöst wird, oder einem leeren String, wenn ein Fehler auftritt.
 */
async function get_ls_result(dir_path) {
    try {
        // Sicherstellen, dass der Pfad in Anführungszeichen gesetzt wird, um Leerzeichen und Sonderzeichen zu behandeln
        const command = `ls -l "${dir_path}"`;
        const { stdout } = await execAsync(command);
        return stdout;
    } catch (error) {
        // Bei jedem Fehler (Verzeichnis nicht gefunden, Berechtigungsfehler, etc.) wird ein leerer String zurückgegeben
        return '';
    }
}