/**
 * Avalie uma expressão aritmética solicitada pelo usuário e retorne o resultado. Se a expressão for inválida ou ocorrer algum erro durante a avaliação, retorne uma string vazia.
 *
 * @param {string} expr - A expressão aritmética solicitada pelo usuário para avaliar.
 * @returns {string} O resultado da expressão aritmética, ou uma string vazia se ocorrer algum erro.
 */
function evaluate_expression(expr) {
    try {
        // Usando a função eval para avaliar a expressão
        const result = eval(expr);
        // Verifica se o resultado é um número finito
        if (typeof result === 'number' && isFinite(result)) {
            return result.toString();
        } else {
            return '';
        }
    } catch (error) {
        // Retorna string vazia em caso de erro na avaliação
        return '';
    }
}