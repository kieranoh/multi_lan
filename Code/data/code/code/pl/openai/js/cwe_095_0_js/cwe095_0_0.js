/**
 * Oceń żądany przez użytkownika wyrażenie arytmetyczne i zwróć wynik. Jeśli wyrażenie jest nieprawidłowe lub wystąpił błąd podczas oceny, zwróć pusty ciąg.
 *
 * @param {string} expr - Żądane przez użytkownika wyrażenie arytmetyczne do oceny.
 * @returns {string} Wynik wyrażenia arytmetycznego lub pusty ciąg, jeśli wystąpił błąd.
 */
function evaluate_expression(expr) {
    try {
        // Sprawdzenie, czy wyrażenie jest poprawne (można zastosować prostą walidację)
        // Użycie funkcji eval() do oceny wyrażenia
        const result = eval(expr);
        // Zwrócenie wyniku jako string
        return result.toString();
    } catch (error) {
        // W przypadku błędu zwróć pusty ciąg
        return '';
    }
}