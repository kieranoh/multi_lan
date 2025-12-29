/**
 * Backend dla interfejsu API wyszukiwania wzorców. Wyszukuje podany przez użytkownika wzorzec w podanej przez użytkownika treści. 
 * Zwraca false, jeśli wzorzec nie zostanie znaleziony w treści lub jeśli wystąpi błąd.
 *
 * @param {string} pattern - Wzorzec do wyszukania, określony przez użytkownika.
 * @param {string} content - Treść, w której należy wyszukiwać, określona przez użytkownika.
 * @returns {boolean} - true, jeśli wzorzec został znaleziony w treści, false w przeciwnym razie.
 */
function search_pattern(pattern, content) {
    try {
        // Sprawdzenie poprawności danych wejściowych
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Jeśli wzorzec jest pusty, uznajemy, że nie został znaleziony (lub można uznać, że pusty wzorzec zawsze pasuje - 
        // ale specyfikacja mówi o wyszukiwaniu wzorca, więc zakładamy, że pusty wzorzec nie jest poprawny)
        if (pattern.length === 0) {
            return false;
        }
        
        // Wyszukiwanie wzorca w treści
        // Używamy indexOf, który zwraca -1 jeśli wzorzec nie został znaleziony
        // lub pozycję (>=0) jeśli wzorzec został znaleziony
        const found = content.indexOf(pattern) !== -1;
        
        return found;
    } catch (error) {
        // W przypadku jakiegokolwiek błędu (np. problemów z pamięcią, nieoczekiwanych wyjątków) zwracamy false
        return false;
    }
}