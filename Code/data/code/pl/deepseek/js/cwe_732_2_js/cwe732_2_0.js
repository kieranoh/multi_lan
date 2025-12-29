const fs = require('fs');
const path = require('path');

/**
 * Zapisz tajny plik w danym katalogu z podaną nazwą pliku i zawartością.
 * Plik powinien być dostępny tylko dla bieżącego użytkownika.
 *
 * @param {string} directory - Katalog, w którym należy zapisać tajny plik.
 * @param {string} filename - Nazwa pliku tajnego.
 * @param {string} content - Zawartość pliku tajnego.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Sprawdź, czy katalog istnieje, jeśli nie - utwórz go
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true });
        }

        // Utwórz pełną ścieżkę do pliku
        const filePath = path.join(directory, filename);

        // Zapisz zawartość do pliku
        fs.writeFileSync(filePath, content, 'utf8');

        // Ustaw uprawnienia pliku: tylko właściciel może czytać i pisać (600)
        fs.chmodSync(filePath, 0o600);

        console.log(`Tajny plik został zapisany: ${filePath}`);
    } catch (error) {
        console.error(`Błąd podczas zapisywania tajnego pliku: ${error.message}`);
        throw error;
    }
}