function evaluate_expression(expr) {
    // Eliminar espais en blanc
    expr = expr.trim();
    
    // Comprovar si l'expressió està buida
    if (expr === '') {
        return '';
    }
    
    // Comprovar caràcters no permesos per seguretat
    // Permetem dígits, operadors aritmètics bàsics, parèntesis i punt decimal
    const allowedChars = /^[0-9+\-*/().\s]+$/;
    if (!allowedChars.test(expr)) {
        return '';
    }
    
    // Comprovar parèntesis balancejats
    let balance = 0;
    for (let i = 0; i < expr.length; i++) {
        if (expr[i] === '(') {
            balance++;
        } else if (expr[i] === ')') {
            balance--;
            if (balance < 0) {
                return '';
            }
        }
    }
    if (balance !== 0) {
        return '';
    }
    
    // Comprovar errors de sintaxi bàsics
    // No permetre dos operadors consecutius (excepte +- com a signe negatiu)
    const operatorRegex = /[+\-*/]/;
    for (let i = 0; i < expr.length - 1; i++) {
        if (operatorRegex.test(expr[i]) && operatorRegex.test(expr[i + 1])) {
            // Comprovar si és un signe negatiu vàlid
            if (!(expr[i + 1] === '-' && /[+\-*/(]/.test(expr[i]))) {
                return '';
            }
        }
    }
    
    // Comprovar que no comenci amb operador (excepte + o -)
    if (expr.length > 0 && /[*/]/.test(expr[0])) {
        return '';
    }
    
    // Comprovar que no acabi amb operador
    if (expr.length > 0 && operatorRegex.test(expr[expr.length - 1])) {
        return '';
    }
    
    try {
        // Reemplaçar expressions com "(-" per "(0-" per a una avaluació correcta
        let processedExpr = expr.replace(/\(-/g, '(0-');
        
        // Si comença amb "-", afegir "0" al principi
        if (processedExpr.startsWith('-')) {
            processedExpr = '0' + processedExpr;
        }
        
        // Utilitzar Function constructor per avaluar l'expressió
        // Això és més segur que eval() però encara requereix precaució
        const result = new Function('return ' + processedExpr)();
        
        // Comprovar si el resultat és un número vàlid
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Retornar el resultat com a cadena
        // Si és un enter, retornar sense decimals
        if (Number.isInteger(result)) {
            return result.toString();
        } else {
            // Retornar amb un màxim de 10 decimals i eliminar zeros innecessaris
            return parseFloat(result.toFixed(10)).toString();
        }
        
    } catch (error) {
        // Capturar qualsevol error durant l'avaluació
        return '';
    }
}