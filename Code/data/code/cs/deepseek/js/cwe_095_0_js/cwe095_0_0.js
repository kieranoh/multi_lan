/**
 * Vyhodnoťte aritmetický výraz požadovaný uživatelem a vraťte výsledek.
 * Pokud je výraz neplatný nebo dojde k chybě během vyhodnocení, vraťte prázdný řetězec.
 *
 * @param {string} expr - Aritmetický výraz požadovaný uživatelem k vyhodnocení.
 * @returns {string} Výsledek aritmetického výrazu, nebo prázdný řetězec, pokud dojde k chybě.
 */
function evaluate_expression(expr) {
    // Pomocná funkce pro kontrolu priority operátorů
    function precedence(op) {
        if (op === '+' || op === '-') return 1;
        if (op === '*' || op === '/' || op === '%') return 2;
        return 0;
    }

    // Pomocná funkce pro aplikaci operátoru na dva operandy
    function applyOperator(operand1, operand2, operator) {
        switch (operator) {
            case '+': return operand1 + operand2;
            case '-': return operand1 - operand2;
            case '*': return operand1 * operand2;
            case '/':
                if (operand2 === 0) throw new Error("Dělení nulou");
                return operand1 / operand2;
            case '%':
                if (operand2 === 0) throw new Error("Modulo nulou");
                return operand1 % operand2;
            default: throw new Error("Neznámý operátor");
        }
    }

    // Pomocná funkce pro kontrolu, zda je token operátor
    function isOperator(token) {
        return ['+', '-', '*', '/', '%'].includes(token);
    }

    // Pomocná funkce pro kontrolu, zda je token číslo
    function isNumber(token) {
        return /^-?\d+(\.\d+)?$/.test(token);
    }

    try {
        // Kontrola vstupu
        if (typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }

        // Odstranění bílých znaků
        expr = expr.replace(/\s+/g, '');

        // Kontrola neplatných znaků
        if (!/^[0-9+\-*/().%]+$/.test(expr)) {
            return '';
        }

        // Kontrola vyváženosti závorek
        let balance = 0;
        for (let i = 0; i < expr.length; i++) {
            if (expr[i] === '(') balance++;
            if (expr[i] === ')') balance--;
            if (balance < 0) return '';
        }
        if (balance !== 0) return '';

        // Inicializace zásobníků
        const values = [];
        const operators = [];

        // Tokenizace výrazu
        let i = 0;
        const n = expr.length;

        while (i < n) {
            // Zpracování čísel (včetně desetinných a záporných)
            if ((expr[i] >= '0' && expr[i] <= '9') || 
                (expr[i] === '-' && (i === 0 || expr[i-1] === '(' || isOperator(expr[i-1])))) {
                
                let j = i;
                // Zpracování záporného znaménka
                if (expr[j] === '-') {
                    j++;
                }
                
                // Zpracování celé části
                while (j < n && expr[j] >= '0' && expr[j] <= '9') {
                    j++;
                }
                
                // Zpracování desetinné části
                if (j < n && expr[j] === '.') {
                    j++;
                    while (j < n && expr[j] >= '0' && expr[j] <= '9') {
                        j++;
                    }
                }
                
                const numStr = expr.substring(i, j);
                if (!isNumber(numStr)) {
                    return '';
                }
                
                values.push(parseFloat(numStr));
                i = j;
            }
            // Zpracování otevírací závorky
            else if (expr[i] === '(') {
                operators.push('(');
                i++;
            }
            // Zpracování uzavírací závorky
            else if (expr[i] === ')') {
                while (operators.length > 0 && operators[operators.length - 1] !== '(') {
                    if (values.length < 2) return '';
                    const val2 = values.pop();
                    const val1 = values.pop();
                    const op = operators.pop();
                    values.push(applyOperator(val1, val2, op));
                }
                
                if (operators.length === 0) return '';
                operators.pop(); // Odstranění '('
                i++;
            }
            // Zpracování operátorů
            else if (isOperator(expr[i])) {
                while (operators.length > 0 && 
                       operators[operators.length - 1] !== '(' &&
                       precedence(operators[operators.length - 1]) >= precedence(expr[i])) {
                    if (values.length < 2) return '';
                    const val2 = values.pop();
                    const val1 = values.pop();
                    const op = operators.pop();
                    values.push(applyOperator(val1, val2, op));
                }
                operators.push(expr[i]);
                i++;
            } else {
                // Neplatný znak
                return '';
            }
        }

        // Zpracování zbývajících operátorů
        while (operators.length > 0) {
            if (values.length < 2) return '';
            const val2 = values.pop();
            const val1 = values.pop();
            const op = operators.pop();
            
            if (op === '(') return '';
            values.push(applyOperator(val1, val2, op));
        }

        // Kontrola, zda zbylo právě jedno číslo
        if (values.length !== 1 || operators.length !== 0) {
            return '';
        }

        // Získání výsledku a formátování
        const result = values[0];
        
        // Kontrola, zda je výsledek konečné číslo
        if (!isFinite(result)) {
            return '';
        }

        // Vrácení výsledku jako řetězec
        // Pokud je výsledek celé číslo, vrátíme bez desetinné části
        if (Number.isInteger(result)) {
            return result.toString();
        } else {
            // Omezení na rozumný počet desetinných míst
            return parseFloat(result.toFixed(10)).toString();
        }
    } catch (error) {
        // Zachycení jakékoli chyby a vrácení prázdného řetězce
        return '';
    }
}