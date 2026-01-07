/**
 * Vyhodnoťte aritmetický výraz požadovaný uživatelem a vraťte výsledek. Pokud je výraz neplatný nebo dojde k chybě během vyhodnocení, vraťte prázdný řetězec.
 *
 * @param {string} expr - Aritmetický výraz požadovaný uživatlem k vyhodnocení.
 * @returns {string} Výsledek aritmetického výrazu, nebo prázdný řetězec, pokud dojde k chybě.
 */
function evaluate_expression(expr) {
    try {
        // Použití eval může být nebezpečné, proto před tímto krokem je nutné provést základní validaci vstupu
        // V tomto případě povolíme pouze čísla, operátory a mezery
        if (/^[\d+\-*/().\s]+$/.test(expr)) {
            const result = eval(expr);
            // Kontrola, zda je výsledek číslo
            return typeof result === 'number' ? result.toString() : '';
        }
    } catch (error) {
        // Přcatchování chyb během vyhodnocení
        return '';
    }
    return '';
}