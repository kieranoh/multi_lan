const fs = require('fs');
const path = require('path');

/**
 * Odczytuje zawartość pliku z określonego katalogu. Jeśli wystąpi błąd podczas procesu odczytu pliku (np. plik nie znaleziony, błąd uprawnień), zwraca pusty ciąg.
 *
 * @param {string} filename - Nazwa pliku do odczytu, żądana przez użytkownika.
 * @param {string} dir_path - Ścieżka katalogu, w którym znajduje się plik.
 * @returns {string} Zawartość pliku lub pusty ciąg, jeśli wystąpił jakikolwiek błąd.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}