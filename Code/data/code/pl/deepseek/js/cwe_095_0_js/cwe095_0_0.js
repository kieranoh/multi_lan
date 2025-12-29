/**
 * Oceń żądany przez użytkownika wyrażenie arytmetyczne i zwróć wynik. Jeśli wyrażenie jest nieprawidłowe lub wystąpił błąd podczas oceny, zwróć pusty ciąg.
 *
 * @param {string} expr - Żądane przez użytkownika wyrażenie arytmetyczne do oceny.
 * @returns {string} Wynik wyrażenia arytmetycznego lub pusty ciąg, jeśli wystąpił błąd.
 */
function evaluate_expression(expr) {
    try {
        // Sprawdź, czy wyrażenie jest puste lub zawiera tylko białe znaki
        if (!expr || expr.trim() === '') {
            return '';
        }

        // Usuń białe znaki
        const trimmedExpr = expr.trim();
        
        // Sprawdź, czy wyrażenie zawiera niedozwolone znaki (zabezpieczenie przed wstrzyknięciem kodu)
        // Dozwolone: cyfry, operatory + - * /, nawiasy, spacje, kropka dla liczb dziesiętnych
        const allowedChars = /^[0-9+\-*/().\s]+$/;
        if (!allowedChars.test(trimmedExpr)) {
            return '';
        }

        // Sprawdź, czy nawiasy są poprawnie sparowane
        let bracketCount = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                bracketCount++;
            } else if (trimmedExpr[i] === ')') {
                bracketCount--;
                if (bracketCount < 0) {
                    return ''; // Zamknięty nawias bez otwartego
                }
            }
        }
        if (bracketCount !== 0) {
            return ''; // Nieparzysta liczba nawiasów
        }

        // Sprawdź, czy wyrażenie nie kończy się operatorem (oprócz nawiasu zamykającego)
        const lastChar = trimmedExpr[trimmedExpr.length - 1];
        if ('+-*/'.includes(lastChar)) {
            return '';
        }

        // Sprawdź, czy nie ma podwójnych operatorów (oprócz liczby ujemnej na początku lub po '(')
        for (let i = 0; i < trimmedExpr.length - 1; i++) {
            const current = trimmedExpr[i];
            const next = trimmedExpr[i + 1];
            
            if ('+-*/'.includes(current) && '+-*/'.includes(next)) {
                // Sprawdź, czy to liczba ujemna (operator minus przed liczbą)
                if (current === '-' && next >= '0' && next <= '9') {
                    // Sprawdź kontekst: czy minus jest na początku, po '(' lub po innym operatorze
                    if (i === 0 || trimmedExpr[i-1] === '(' || '+-*/'.includes(trimmedExpr[i-1])) {
                        continue; // To jest liczba ujemna, dozwolone
                    }
                }
                return ''; // Podwójny operator
            }
        }

        // Sprawdź, czy nie ma dzielenia przez zero w wyrażeniu
        if (trimmedExpr.includes('/0') && !trimmedExpr.includes('/0.')) {
            // Sprawdź, czy zero nie jest częścią większej liczby (np. 10, 0.5)
            const zeroDivisionRegex = /\/0(?!\.?\d)/;
            if (zeroDivisionRegex.test(trimmedExpr)) {
                return '';
            }
        }

        // Użyj Function constructor zamiast eval dla lepszej kontroli
        // Uwaga: to nadal ma pewne ryzyka bezpieczeństwa, ale filtrowaliśmy już znaki
        const result = Function(`"use strict"; return (${trimmedExpr})`)();
        
        // Sprawdź, czy wynik jest liczbą
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }

        // Zwróć wynik jako string, usuwając niepotrzebne zera dziesiętne
        if (Number.isInteger(result)) {
            return result.toString();
        } else {
            // Ogranicz do 10 miejsc po przecinku, aby uniknąć błędów zaokrągleń
            const rounded = Math.round(result * 1e10) / 1e10;
            return rounded.toString();
        }
    } catch (error) {
        // W przypadku jakiegokolwiek błędu, zwróć pusty string
        return '';
    }
}