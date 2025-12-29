/**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    try {
        // Check if expression is empty or contains only whitespace
        if (!expr || expr.trim() === '') {
            return '';
        }
        
        // Remove all whitespace from the expression
        const cleanExpr = expr.replace(/\s+/g, '');
        
        // Validate the expression contains only allowed characters
        // Allowed: digits 0-9, decimal point, operators + - * /, parentheses
        if (!/^[\d+\-*/().]+$/.test(cleanExpr)) {
            return '';
        }
        
        // Validate parentheses are balanced
        let balance = 0;
        for (let i = 0; i < cleanExpr.length; i++) {
            if (cleanExpr[i] === '(') {
                balance++;
            } else if (cleanExpr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        if (balance !== 0) {
            return '';
        }
        
        // Validate expression doesn't have invalid operator sequences
        // Check for consecutive operators (except for unary minus at the beginning or after '(')
        for (let i = 0; i < cleanExpr.length - 1; i++) {
            const current = cleanExpr[i];
            const next = cleanExpr[i + 1];
            
            // Check for two operators in a row (with exceptions for unary minus)
            if ('+-*/'.includes(current) && '+-*/'.includes(next)) {
                // Allow unary minus: "-5", "(-5)", "*-5" etc.
                // But not "++", "+*", "*/" etc.
                if (next !== '-') {
                    return '';
                }
                // Check if the minus is actually a unary minus
                // It's unary if it's at the start, after '(', or after another operator
                if (i === 0 || cleanExpr[i - 1] === '(' || '+-*/'.includes(cleanExpr[i - 1])) {
                    // This is valid unary minus, continue
                } else {
                    return '';
                }
            }
        }
        
        // Validate no division by zero in obvious cases
        if (cleanExpr.includes('/0') && !cleanExpr.includes('/0.')) {
            // Check if it's really division by zero (not part of a larger number like 10, 0.5, etc.)
            for (let i = 0; i < cleanExpr.length - 1; i++) {
                if (cleanExpr[i] === '/' && cleanExpr[i + 1] === '0') {
                    // Check if it's followed by a decimal point or end of expression/non-digit
                    if (i + 2 >= cleanExpr.length || !/\d/.test(cleanExpr[i + 2])) {
                        return '';
                    }
                }
            }
        }
        
        // Use Function constructor to evaluate the expression safely
        // This is safer than eval() but still has some risks, so we've done validation above
        const result = new Function(`return ${cleanExpr}`)();
        
        // Check if result is a valid number
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Convert to string, handling floating point precision issues
        let resultStr = result.toString();
        
        // If it's a decimal, limit to reasonable precision to avoid floating point errors
        if (resultStr.includes('.')) {
            // Parse as float and round to 10 decimal places to avoid floating point precision issues
            const rounded = Math.round(result * 1e10) / 1e10;
            resultStr = rounded.toString();
            
            // Remove trailing zeros after decimal point
            resultStr = resultStr.replace(/(\.\d*?[1-9])0+$/, '$1');
            resultStr = resultStr.replace(/\.0+$/, '');
        }
        
        return resultStr;
        
    } catch (error) {
        // Catch any evaluation errors and return empty string
        return '';
    }
}