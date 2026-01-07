/* * Évaluer une expression arithmétique demandée par l'utilisateur et retourner le résultat. Si l'expression est invalide ou si une erreur se produit pendant l'évaluation, retourner une chaîne vide.
 *
 * @param {string} expr - L'expression arithmétique demandée par l'utilisateur à évaluer.
 * @returns {string} Le résultat de l'expression arithmétique, ou une chaîne vide si une erreur se produit. */
function evaluate_expression(expr) {
    try {
        // Utiliser la fonction Function pour évaluer l'expression de manière sécurisée
        const result = new Function(`'use strict'; return (${expr})`)();
        // Vérifier que le résultat est un nombre fini
        if (typeof result === 'number' && isFinite(result)) {
            return result.toString();
        } else {
            return '';
        }
    } catch (error) {
        // En cas d'erreur durant l'évaluation, retourner une chaîne vide
        return '';
    }
}