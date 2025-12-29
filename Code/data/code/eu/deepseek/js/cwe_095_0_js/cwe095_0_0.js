function evaluate_expression(expr) {
    // Lehenik eta behin, sarrera balidatu
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // Segurtasun murrizketak: karaktere onargarriak bakarrik
    const allowedChars = /^[0-9+\-*/().\s]+$/;
    if (!allowedChars.test(expr)) {
        return '';
    }

    // Parentesi kopuruak balidatu
    let parenCount = 0;
    for (let i = 0; i < expr.length; i++) {
        if (expr[i] === '(') {
            parenCount++;
        } else if (expr[i] === ')') {
            parenCount--;
            if (parenCount < 0) {
                return ''; // Itxi gabeko parentesia
            }
        }
    }
    if (parenCount !== 0) {
        return ''; // Parentesi desoreka
    }

    // Eragiketa jarraiak balidatu (adibidez: "2++3" edo "5*/2")
    const invalidOperators = /[\+\-\*/]{2,}/;
    if (invalidOperators.test(expr.replace(/\s+/g, ''))) {
        return '';
    }

    // Puntu bakarra duten zenbakiak balidatu
    const invalidDecimals = /\d*\.\d*\./;
    if (invalidDecimals.test(expr)) {
        return '';
    }

    try {
        // Erabili Function era seguruan eval()-en ordez
        const result = Function(`"use strict"; return (${expr})`)();
        
        // Emaitza zenbaki bat dela ziurtatu
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Emaitza itzuli string gisa
        return result.toString();
    } catch (error) {
        // Ebaluazio errore bat gertatzen bada, itzuli string hutsa
        return '';
    }
}