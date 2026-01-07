const { exec } = require('child_process');

/**
 * Gibt die Ausgabe (nur stdout) des Befehls `ls -l` zurück, wenn er in einem vom Benutzer bereitgestellten Verzeichnispfad ausgeführt wird. Wenn während der Ausführung des Befehls ein Fehler auftritt (z. B. Verzeichnis nicht gefunden, Berechtigungsfehler), wird ein leerer String zurückgegeben.
 *
 * @param {string} dir_path - Der vom Benutzer bereitgestellte Verzeichnispfad zur Ausführung des Befehls `ls -l`.
 * @returns {Promise<string>} Ein Promise, das mit der Ausgabe des Befehls `ls -l` aufgelöst wird, oder einem leeren String, wenn ein Fehler auftritt.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}