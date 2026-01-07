/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 * 
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    // 입력이 문자열이 아니거나 비어있는 경우 빈 문자열 반환
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // 표현식에서 공백 제거
    const trimmedExpr = expr.trim();
    
    // 안전 검사: 허용된 문자만 포함하는지 확인 (숫자, 연산자, 괄호, 소수점, 공백)
    const safePattern = /^[\d+\-*/().\s]+$/;
    if (!safePattern.test(trimmedExpr)) {
        return '';
    }

    // 위험한 함수 호출 방지를 위한 추가 검사
    const dangerousPatterns = [
        /eval\(/i,
        /Function\(/i,
        /setTimeout\(/i,
        /setInterval\(/i,
        /new Function\(/i,
        /\.constructor\(/i,
        /import\(/i,
        /require\(/i,
        /process\./i,
        /window\./i,
        /document\./i,
        /alert\(/i,
        /console\./i
    ];
    
    for (const pattern of dangerousPatterns) {
        if (pattern.test(trimmedExpr)) {
            return '';
        }
    }

    try {
        // 괄호 쌍이 맞는지 확인
        const stack = [];
        for (let i = 0; i < trimmedExpr.length; i++) {
            const char = trimmedExpr[i];
            if (char === '(') {
                stack.push('(');
            } else if (char === ')') {
                if (stack.length === 0) {
                    return '';
                }
                stack.pop();
            }
        }
        
        if (stack.length !== 0) {
            return '';
        }

        // 연산자 우선순위를 고려한 안전한 평가
        // 1. 괄호 안의 표현식 먼저 처리
        // 2. 곱셈과 나눗셈 처리
        // 3. 덧셈과 뺄셈 처리
        
        // 간단한 표현식 평가를 위한 보조 함수
        const evaluateSimple = (expression) => {
            // 연산자 분리
            const tokens = expression.match(/(\d+(?:\.\d+)?|[+\-*/])/g);
            if (!tokens) {
                return '';
            }

            // 숫자와 연산자 분리
            const numbers = [];
            const operators = [];
            
            for (const token of tokens) {
                if (token.match(/^\d+(?:\.\d+)?$/)) {
                    numbers.push(parseFloat(token));
                } else if (token.match(/^[+\-*/]$/)) {
                    operators.push(token);
                }
            }
            
            // 숫자 개수가 연산자 개수보다 1개 많아야 함
            if (numbers.length !== operators.length + 1) {
                return '';
            }
            
            // 곱셈과 나눗셈 먼저 처리
            let i = 0;
            while (i < operators.length) {
                if (operators[i] === '*' || operators[i] === '/') {
                    const left = numbers[i];
                    const right = numbers[i + 1];
                    let result;
                    
                    if (operators[i] === '*') {
                        result = left * right;
                    } else {
                        if (right === 0) {
                            return ''; // 0으로 나누기 방지
                        }
                        result = left / right;
                    }
                    
                    // 결과 적용
                    numbers.splice(i, 2, result);
                    operators.splice(i, 1);
                } else {
                    i++;
                }
            }
            
            // 덧셈과 뺄셈 처리
            let finalResult = numbers[0];
            for (let j = 0; j < operators.length; j++) {
                if (operators[j] === '+') {
                    finalResult += numbers[j + 1];
                } else if (operators[j] === '-') {
                    finalResult -= numbers[j + 1];
                }
            }
            
            return finalResult;
        };

        // 괄호 처리
        const evaluateWithParentheses = (expression) => {
            let expr = expression;
            
            // 가장 안쪽의 괄호부터 처리
            while (expr.includes('(')) {
                const lastOpen = expr.lastIndexOf('(');
                const nextClose = expr.indexOf(')', lastOpen);
                
                if (nextClose === -1) {
                    return '';
                }
                
                const innerExpr = expr.substring(lastOpen + 1, nextClose);
                const innerResult = evaluateSimple(innerExpr);
                
                if (innerResult === '') {
                    return '';
                }
                
                // 괄호 안의 결과로 대체
                expr = expr.substring(0, lastOpen) + innerResult + expr.substring(nextClose + 1);
            }
            
            // 남은 표현식 평가
            return evaluateSimple(expr);
        };

        const result = evaluateWithParentheses(trimmedExpr);
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 소수점 이하 10자리까지 제한하여 반환
        const roundedResult = Math.round(result * 10000000000) / 10000000000;
        
        // 불필요한 소수점 제거
        if (roundedResult % 1 === 0) {
            return roundedResult.toString();
        }
        
        return roundedResult.toString();
        
    } catch (error) {
        // 모든 오류는 빈 문자열 반환
        return '';
    }
}