/**
 * Evalúa una expresión aritmética solicitada por el usuario y devuelve el resultado. Si la expresión es inválida o ocurre algún error durante la evaluación, devuelve una cadena vacía.
 *
 * @param {string} expr - La expresión aritmética solicitada por el usuario para evaluar.
 * @returns {string} El resultado de la expresión aritmética, o una cadena vacía si ocurre algún error.
 */
function evaluate_expression(expr) {
    try {
        // Verificar si la expresión es nula, indefinida o vacía
        if (expr === null || expr === undefined || expr.trim() === '') {
            return '';
        }
        
        // Eliminar espacios en blanco
        const trimmedExpr = expr.trim();
        
        // Validar caracteres permitidos: dígitos, operadores aritméticos básicos, paréntesis y punto decimal
        const validCharsRegex = /^[0-9+\-*/().\s]+$/;
        if (!validCharsRegex.test(trimmedExpr)) {
            return '';
        }
        
        // Validar paréntesis balanceados
        let balance = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                balance++;
            } else if (trimmedExpr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        if (balance !== 0) {
            return '';
        }
        
        // Validar que no haya operadores consecutivos inválidos
        const invalidOperatorSequence = /[+\-*/]{2,}/;
        if (invalidOperatorSequence.test(trimmedExpr.replace(/\s+/g, ''))) {
            // Permitir números negativos como -5 o -(3+2)
            const negativeNumberPattern = /[+\-*/]\(/;
            const startsWithNegative = trimmedExpr.match(/^-\d/);
            const hasValidNegative = trimmedExpr.match(/[+\-*/]-\d/);
            
            // Si no es un número negativo válido, retornar vacío
            if (!startsWithNegative && !hasValidNegative && !negativeNumberPattern.test(trimmedExpr)) {
                return '';
            }
        }
        
        // Validar estructura básica de la expresión
        // No debe terminar con un operador (excepto si es un número negativo al final, lo cual no es válido)
        const endsWithOperator = /[+\-*/]$/;
        if (endsWithOperator.test(trimmedExpr.trim())) {
            return '';
        }
        
        // No debe empezar con operador (excepto el signo negativo para números negativos)
        const startsWithInvalidOperator = /^[+*/]/;
        if (startsWithInvalidOperator.test(trimmedExpr.trim())) {
            return '';
        }
        
        // Usar Function constructor para evaluar de forma segura
        // Esto es más seguro que eval() directo porque limita el contexto
        const safeEval = new Function('return ' + trimmedExpr);
        const result = safeEval();
        
        // Verificar que el resultado sea un número finito
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Devolver el resultado como string
        return String(result);
        
    } catch (error) {
        // Cualquier error durante la evaluación resulta en cadena vacía
        return '';
    }
}