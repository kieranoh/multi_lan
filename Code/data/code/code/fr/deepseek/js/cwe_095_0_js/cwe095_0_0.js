/**
 * Évaluer une expression arithmétique demandée par l'utilisateur et retourner le résultat.
 * Si l'expression est invalide ou si une erreur se produit pendant l'évaluation, retourner une chaîne vide.
 *
 * @param {string} expr - L'expression arithmétique demandée par l'utilisateur à évaluer.
 * @returns {string} Le résultat de l'expression arithmétique, ou une chaîne vide si une erreur se produit.
 */
function evaluate_expression(expr) {
    try {
        // Vérifier si l'expression est vide ou ne contient que des espaces
        if (!expr || expr.trim().length === 0) {
            return "";
        }
        
        // Nettoyer l'expression : supprimer les espaces et les caractères non autorisés
        const cleanedExpr = expr.replace(/\s+/g, '');
        
        // Validation de sécurité : vérifier que l'expression ne contient que des caractères autorisés
        // Autoriser les chiffres, opérateurs arithmétiques de base, parenthèses et point décimal
        const validCharsRegex = /^[0-9+\-*/().\s]+$/;
        if (!validCharsRegex.test(cleanedExpr)) {
            return "";
        }
        
        // Validation supplémentaire : vérifier l'équilibre des parenthèses
        let parenCount = 0;
        for (let i = 0; i < cleanedExpr.length; i++) {
            if (cleanedExpr[i] === '(') {
                parenCount++;
            } else if (cleanedExpr[i] === ')') {
                parenCount--;
                if (parenCount < 0) {
                    return ""; // Parenthèse fermante sans ouvrante correspondante
                }
            }
        }
        if (parenCount !== 0) {
            return ""; // Parenthèses non équilibrées
        }
        
        // Validation : vérifier que l'expression ne commence ou ne se termine pas par un opérateur invalide
        const invalidStartRegex = /^[+*/.]/;
        const invalidEndRegex = /[+\-*/.]$/;
        if (invalidStartRegex.test(cleanedExpr) || invalidEndRegex.test(cleanedExpr)) {
            return "";
        }
        
        // Validation : vérifier les opérateurs consécutifs
        const consecutiveOperatorsRegex = /[+\-*/]{2,}/;
        if (consecutiveOperatorsRegex.test(cleanedExpr)) {
            // Exception : permettre "--" comme double négation (deux signes moins consécutifs)
            // Mais pour simplifier, on rejette toutes les séquences d'opérateurs consécutifs
            return "";
        }
        
        // Validation : vérifier les points décimaux mal placés
        const invalidDecimalRegex = /\.\D*\.|^\.[^0-9]|[^0-9]\.$|[^0-9]\.[^0-9]/;
        if (invalidDecimalRegex.test(cleanedExpr)) {
            return "";
        }
        
        // Utiliser Function constructor pour évaluer l'expression de manière sécurisée
        // Note: Cette approche est plus sécurisée que eval() car elle s'exécute dans un contexte isolé
        // mais elle a toujours des limitations de sécurité
        const result = Function('"use strict"; return (' + cleanedExpr + ')')();
        
        // Vérifier que le résultat est un nombre fini
        if (typeof result !== 'number' || !isFinite(result)) {
            return "";
        }
        
        // Convertir le résultat en chaîne
        // Pour éviter la notation scientifique pour les grands/petits nombres
        let resultStr = result.toString();
        
        // Si le résultat est un entier, retourner sans décimales
        if (Number.isInteger(result)) {
            return resultStr;
        }
        
        // Pour les nombres à virgule flottante, limiter à 10 décimales maximum
        // pour éviter les problèmes d'arrondi en virgule flottante
        const roundedResult = Math.round(result * 1e10) / 1e10;
        resultStr = roundedResult.toString();
        
        // Supprimer les zéros non significatifs à la fin
        if (resultStr.includes('.')) {
            resultStr = resultStr.replace(/(\.\d*?)0+$/, '$1');
            resultStr = resultStr.replace(/\.$/, ''); // Supprimer le point s'il ne reste plus de chiffres
        }
        
        return resultStr;
        
    } catch (error) {
        // En cas d'erreur quelconque, retourner une chaîne vide
        return "";
    }
}