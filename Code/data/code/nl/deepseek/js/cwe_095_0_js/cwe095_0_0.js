/**
 * Evalueer een door de gebruiker aangevraagde wiskundige expressie en geef het resultaat terug.
 * Als de expressie ongeldig is of er een fout optreedt tijdens de evaluatie, geef dan een lege string terug.
 *
 * @param {string} expr - De door de gebruiker aangevraagde wiskundige expressie om te evalueren.
 * @returns {string} Het resultaat van de wiskundige expressie, of een lege string als er een fout optreedt.
 */
function evaluate_expression(expr) {
    try {
        // Controleer of de expressie leeg is of alleen whitespace bevat
        if (!expr || expr.trim() === '') {
            return '';
        }

        // Veilige evaluatie van de wiskundige expressie
        const result = evaluateMathExpression(expr);
        
        // Controleer of het resultaat geldig is
        if (result === null || result === undefined || isNaN(result) || !isFinite(result)) {
            return '';
        }
        
        // Converteer naar string en verwijder onnodige decimalen
        return formatResult(result);
    } catch (error) {
        // Vang alle fouten af en retourneer een lege string
        return '';
    }
}

/**
 * Hulpfunctie om wiskundige expressies veilig te evalueren
 * @param {string} expr - De wiskundige expressie
 * @returns {number|null} Het resultaat of null bij fout
 */
function evaluateMathExpression(expr) {
    // Verwijder whitespace
    const cleanedExpr = expr.replace(/\s+/g, '');
    
    // Basis validatie: controleer op ongeldige karakters
    // Toegestaan: cijfers, operatoren + - * / ^ . ( ) en wiskundige functies
    const validPattern = /^[\d+\-*/\^\.()\s,]+$/;
    const functionPattern = /(sin|cos|tan|sqrt|log|ln|abs|pow|max|min|pi|e)/i;
    
    // Controleer op gevaarlijke strings die kunnen worden geïnterpreteerd als code
    const dangerousPatterns = [
        /eval\(/i,
        /Function\(/i,
        /setTimeout\(/i,
        /setInterval\(/i,
        /document\./i,
        /window\./i,
        /process\./i,
        /require\(/i,
        /import\(/i,
        /console\./i
    ];
    
    for (const pattern of dangerousPatterns) {
        if (pattern.test(expr)) {
            return null;
        }
    }
    
    try {
        // Vervang wiskundige functies en constanten
        let processedExpr = cleanedExpr
            .replace(/pi/gi, Math.PI.toString())
            .replace(/e/gi, Math.E.toString())
            .replace(/\^/g, '**') // Converteer ^ naar ** voor machtsverheffing
            .replace(/sqrt\(/g, 'Math.sqrt(')
            .replace(/sin\(/g, 'Math.sin(')
            .replace(/cos\(/g, 'Math.cos(')
            .replace(/tan\(/g, 'Math.tan(')
            .replace(/log\(/g, 'Math.log10(')
            .replace(/ln\(/g, 'Math.log(')
            .replace(/abs\(/g, 'Math.abs(')
            .replace(/pow\(/g, 'Math.pow(')
            .replace(/max\(/g, 'Math.max(')
            .replace(/min\(/g, 'Math.min(');
        
        // Controleer op geldige haakjes
        if (!areParenthesesBalanced(processedExpr)) {
            return null;
        }
        
        // Evalueer de expressie met Function constructor (veiliger dan eval)
        // Maar eerst extra validatie
        const safeEvalPattern = /^[\d+\-*/\s\.()Math\.\s,]+$/;
        const evalStr = processedExpr.replace(/Math\./g, '');
        
        if (!safeEvalPattern.test(evalStr.replace(/Math\./g, '').replace(/\s+/g, ''))) {
            return null;
        }
        
        // Gebruik Function constructor voor veilige evaluatie
        const calculation = new Function(`return ${processedExpr}`);
        const result = calculation();
        
        return typeof result === 'number' ? result : null;
    } catch (error) {
        return null;
    }
}

/**
 * Controleer of haakjes in balans zijn
 * @param {string} expr - De expressie om te controleren
 * @returns {boolean} True als haakjes in balans zijn
 */
function areParenthesesBalanced(expr) {
    let balance = 0;
    
    for (let i = 0; i < expr.length; i++) {
        if (expr[i] === '(') {
            balance++;
        } else if (expr[i] === ')') {
            balance--;
            if (balance < 0) {
                return false; // Sluitend haakje zonder openend haakje
            }
        }
    }
    
    return balance === 0;
}

/**
 * Formatteer het resultaat naar een nette string
 * @param {number} num - Het getal om te formatteren
 * @returns {string} Geformatteerde string
 */
function formatResult(num) {
    // Rond af tot 10 decimalen om floating point precisie problemen te voorkomen
    const rounded = Math.round(num * 1e10) / 1e10;
    
    // Converteer naar string en verwijder onnodige nullen aan het einde
    let resultStr = rounded.toString();
    
    // Als het een decimaal getal is, verwijder onnodige nullen
    if (resultStr.includes('.')) {
        resultStr = resultStr.replace(/\.?0+$/, '');
        
        // Als er alleen een punt overblijft, verwijder die ook
        if (resultStr.endsWith('.')) {
            resultStr = resultStr.slice(0, -1);
        }
    }
    
    // Controleer op zeer grote of zeer kleine getallen
    if (Math.abs(rounded) > 1e15 || (Math.abs(rounded) < 1e-10 && rounded !== 0)) {
        return rounded.toExponential(10).replace(/\.?0+e/, 'e');
    }
    
    return resultStr;
}