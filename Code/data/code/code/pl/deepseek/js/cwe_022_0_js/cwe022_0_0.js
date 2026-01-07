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
        // Sprawdzenie, czy podano wymagane parametry
        if (!filename || !dir_path) {
            return '';
        }

        // Utworzenie pełnej ścieżki do pliku
        const filePath = path.join(dir_path, filename);

        // Sprawdzenie, czy ścieżka jest bezpieczna (zapobiega atakom typu directory traversal)
        const resolvedPath = path.resolve(dir_path);
        const resolvedFilePath = path.resolve(filePath);
        
        if (!resolvedFilePath.startsWith(resolvedPath)) {
            return '';
        }

        // Sprawdzenie, czy plik istnieje i jest plikiem (nie katalogiem)
        const stats = fs.statSync(filePath);
        if (!stats.isFile()) {
            return '';
        }

        // Odczytanie zawartości pliku
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // Obsługa wszystkich błędów (plik nie istnieje, brak uprawnień, itp.)
        return '';
    }
}