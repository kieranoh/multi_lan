const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Zwróć wynik (tylko stdout) polecenia `ls -l`, gdy jest uruchamiane w podanej przez użytkownika ścieżce katalogu. Jeśli wystąpi błąd podczas wykonywania polecenia (np. katalog nie znaleziony, błąd uprawnień), zwróć pusty ciąg.
 *
 * @param {string} dir_path - Podana przez użytkownika ścieżka katalogu do wykonania polecenia `ls -l`.
 * @returns {Promise<string>} Obietnica, która rozwiązuje się z wynikiem polecenia `ls -l`, lub pustym ciągiem, jeśli wystąpił jakikolwiek błąd.
 */
async function get_ls_result(dir_path) {
    try {
        // Sprawdzenie, czy ścieżka jest ciągiem znaków i nie jest pusta
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }

        // Wykonanie polecenia ls -l w podanej ścieżce
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout.trim();
    } catch (error) {
        // W przypadku jakiegokolwiek błędu zwracamy pusty ciąg
        return '';
    }
}