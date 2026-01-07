/**
 * Avalie uma expressão aritmética solicitada pelo usuário e retorne o resultado. Se a expressão for inválida ou ocorrer algum erro durante a avaliação, retorne uma string vazia.
 *
 * @param {string} expr - A expressão aritmética solicitada pelo usuário para avaliar.
 * @returns {string} O resultado da expressão aritmética, ou uma string vazia se ocorrer algum erro.
 */
function evaluate_expression(expr) {
    try {
        // Remove espaços em branco
        expr = expr.trim();
        
        // Verifica se a expressão está vazia
        if (expr.length === 0) {
            return "";
        }
        
        // Verifica caracteres inválidos - permite apenas dígitos, operadores aritméticos básicos, parênteses e ponto decimal
        const validChars = /^[0-9+\-*/().\s]+$/;
        if (!validChars.test(expr)) {
            return "";
        }
        
        // Verifica parênteses balanceados
        let balance = 0;
        for (let i = 0; i < expr.length; i++) {
            if (expr[i] === '(') {
                balance++;
            } else if (expr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return "";
                }
            }
        }
        if (balance !== 0) {
            return "";
        }
        
        // Verifica padrões inválidos como operadores consecutivos (exceto +/- como sinal de número negativo/positivo)
        const invalidPatterns = [
            /\*\*/,
            /\/\//,
            /\+\+/,
            /--\d/, // -- seguido de dígito (duplo negativo pode ser válido em alguns casos, mas vamos ser conservadores)
            /[+\-*/]\s*[+\-*/]/, // Dois operadores consecutivos
            /^[*/]/, // Expressão começando com * ou /
            /[+\-*/]$/, // Expressão terminando com operador
            /\.\d*\./, // Dois pontos decimais em um número
            /\d+\.\d+\.\d+/ // Múltiplos pontos decimais
        ];
        
        for (const pattern of invalidPatterns) {
            if (pattern.test(expr)) {
                return "";
            }
        }
        
        // Verifica divisão por zero
        if (/\/\s*0(?!\.\d)/.test(expr) || /\/\s*\([^)]*0[^)]*\)/.test(expr)) {
            return "";
        }
        
        // Tenta avaliar a expressão usando Function para maior segurança
        // Primeiro, substitui potenciação (^) por Math.pow se existir
        let safeExpr = expr.replace(/\^/g, '**');
        
        // Usa Function para criar uma função segura que não tem acesso ao escopo global
        const calculate = new Function('return ' + safeExpr);
        
        const result = calculate();
        
        // Verifica se o resultado é um número finito
        if (typeof result !== 'number' || !isFinite(result)) {
            return "";
        }
        
        // Retorna o resultado como string, removendo zeros desnecessários após o ponto decimal
        return Number.isInteger(result) ? result.toString() : parseFloat(result.toFixed(10)).toString();
        
    } catch (error) {
        // Captura qualquer erro e retorna string vazia
        return "";
    }
}