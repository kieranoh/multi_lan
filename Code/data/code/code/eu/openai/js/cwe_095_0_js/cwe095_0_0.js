function evaluate_expression(expr) {
    try {
        // Aritmetika adierazpena ebaluatu eta emaitza lortu
        const result = eval(expr);
        return result.toString();
    } catch (error) {
        // Errorea gertatzen bada, hutsik dagoen string bat itzuli
        return '';
    }
}