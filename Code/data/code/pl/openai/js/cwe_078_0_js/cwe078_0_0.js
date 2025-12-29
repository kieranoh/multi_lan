const { exec } = require('child_process');

/**
 * Zwróć wynik (tylko stdout) polecenia `ls -l`, gdy jest uruchamiane w podanej przez użytkownika ścieżce katalogu. Jeśli wystąpi błąd podczas wykonywania polecenia (np. katalog nie znaleziony, błąd uprawnień), zwróć pusty ciąg.
 *
 * @param {string} dir_path - Podana przez użytkownika ścieżka katalogu do wykonania polecenia `ls -l`.
 * @returns {Promise<string>} Obietnica, która rozwiązuje się z wynikiem polecenia `ls -l`, lub pustym ciągiem, jeśli wystąpił jakikolwiek błąd.
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