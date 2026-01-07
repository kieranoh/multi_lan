function evaluate_expression(expr) {
    try {
        // 입력이 문자열이 아니거나 비어있는 경우 빈 문자열 반환
        if (typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }

        // 표현식 정리: 공백 제거
        const cleanedExpr = expr.trim();
        
        // 안전 검사: 허용된 문자만 포함하는지 확인
        // 숫자, 기본 연산자(+, -, *, /, %), 괄호, 소수점, 공백만 허용
        const safePattern = /^[\d+\-*/().%\s]+$/;
        if (!safePattern.test(cleanedExpr)) {
            return '';
        }

        // 잠재적인 위험한 패턴 차단
        const dangerousPatterns = [
            /eval\(/i,
            /Function\(/i,
            /setTimeout\(/i,
            /setInterval\(/i,
            /alert\(/i,
            /console\./i,
            /window\./i,
            /document\./i,
            /process\./i,
            /require\(/i,
            /import\(/i,
            /__proto__/,
            /constructor/,
            /prototype/
        ];

        for (const pattern of dangerousPatterns) {
            if (pattern.test(cleanedExpr)) {
                return '';
            }
        }

        // 괄호 짝이 맞는지 확인
        const bracketStack = [];
        for (const char of cleanedExpr) {
            if (char === '(') {
                bracketStack.push('(');
            } else if (char === ')') {
                if (bracketStack.length === 0) {
                    return ''; // 닫는 괄호가 여는 괄호보다 많음
                }
                bracketStack.pop();
            }
        }
        if (bracketStack.length > 0) {
            return ''; // 여는 괄호가 닫는 괄호보다 많음
        }

        // 나누기 0 방지를 위한 검사
        if (cleanedExpr.includes('/0') && !cleanedExpr.includes('/0.')) {
            // '/0'이 있지만 '/0.'이 아닌 경우 (0.0은 허용)
            return '';
        }

        // 표현식 평가
        // Function 생성자를 사용하는 대신 직접 평가
        // 먼저 모든 % 연산자를 수학적 모듈로 연산으로 처리
        let evalExpr = cleanedExpr;
        
        // % 연산자를 JavaScript의 나머지 연산으로 처리
        // 주의: 수학적 모듈로와 JavaScript 나머지는 음수 처리 방식이 다름
        // 여기서는 JavaScript의 나머지 연산을 사용
        
        try {
            // Function 생성자를 사용하는 대신 간단한 파싱과 평가
            // 보안을 위해 괄호와 연산자 우선순위를 고려한 평가 함수 사용
            const result = safeEval(evalExpr);
            
            // 결과가 유효한 숫자인지 확인
            if (typeof result !== 'number' || !isFinite(result)) {
                return '';
            }
            
            // 결과를 문자열로 변환 (불필요한 소수점 제거)
            return formatResult(result);
        } catch (error) {
            return '';
        }
    } catch (error) {
        // 모든 예외를 잡아 빈 문자열 반환
        return '';
    }
}

// 보안을 고려한 안전한 평가 함수
function safeEval(expr) {
    // 연산자 우선순위를 고려한 평가
    // 1. 괄호 처리
    // 2. 곱하기, 나누기, 나머지
    // 3. 더하기, 빼기
    
    // 먼저 괄호 안의 표현식을 재귀적으로 평가
    let currentExpr = expr;
    
    // 괄호 처리
    while (currentExpr.includes('(')) {
        const start = currentExpr.lastIndexOf('(');
        const end = currentExpr.indexOf(')', start);
        
        if (end === -1) {
            throw new Error('Invalid parentheses');
        }
        
        const innerExpr = currentExpr.substring(start + 1, end);
        const innerResult = safeEval(innerExpr);
        
        currentExpr = currentExpr.substring(0, start) + innerResult + currentExpr.substring(end + 1);
    }
    
    // 연산자 우선순위에 따라 평가
    return evaluateWithoutParentheses(currentExpr);
}

function evaluateWithoutParentheses(expr) {
    // 연산자 분리 (음수 기호와 구분하기 위해)
    const tokens = tokenize(expr);
    
    // 첫 번째 패스: *, /, % 처리
    for (let i = 1; i < tokens.length; i += 2) {
        if (tokens[i] === '*' || tokens[i] === '/' || tokens[i] === '%') {
            const left = parseFloat(tokens[i - 1]);
            const right = parseFloat(tokens[i + 1]);
            let result;
            
            switch (tokens[i]) {
                case '*':
                    result = left * right;
                    break;
                case '/':
                    if (right === 0) {
                        throw new Error('Division by zero');
                    }
                    result = left / right;
                    break;
                case '%':
                    result = left % right;
                    break;
            }
            
            // 결과로 토큰 교체
            tokens.splice(i - 1, 3, result.toString());
            i -= 2; // 인덱스 조정
        }
    }
    
    // 두 번째 패스: +, - 처리
    let result = parseFloat(tokens[0]);
    for (let i = 1; i < tokens.length; i += 2) {
        const operator = tokens[i];
        const operand = parseFloat(tokens[i + 1]);
        
        switch (operator) {
            case '+':
                result += operand;
                break;
            case '-':
                result -= operand;
                break;
        }
    }
    
    return result;
}

function tokenize(expr) {
    const tokens = [];
    let currentNumber = '';
    
    for (let i = 0; i < expr.length; i++) {
        const char = expr[i];
        
        if ('+-*/%'.includes(char)) {
            // 연산자 발견
            if (currentNumber !== '') {
                tokens.push(currentNumber);
                currentNumber = '';
            }
            
            // 음수 기호 처리 (첫 번째 토큰이거나 이전 토큰이 연산자인 경우)
            if (char === '-' && (tokens.length === 0 || '+-*/%'.includes(tokens[tokens.length - 1]))) {
                currentNumber += char;
            } else {
                tokens.push(char);
            }
        } else if (char !== ' ') {
            // 숫자나 소수점
            currentNumber += char;
        } else if (currentNumber !== '') {
            // 공백이고 현재 숫자가 있으면 토큰 추가
            tokens.push(currentNumber);
            currentNumber = '';
        }
    }
    
    // 마지막 숫자 추가
    if (currentNumber !== '') {
        tokens.push(currentNumber);
    }
    
    return tokens;
}

function formatResult(num) {
    // 소수점 이하 불필요한 0 제거
    const str = num.toString();
    
    // 과학적 표기법 처리
    if (str.includes('e')) {
        return str;
    }
    
    // 소수점이 있는 경우
    if (str.includes('.')) {
        // 뒤의 0 제거
        let trimmed = str.replace(/\.?0+$/, '');
        // 소수점만 남은 경우 제거
        if (trimmed.endsWith('.')) {
            trimmed = trimmed.slice(0, -1);
        }
        return trimmed;
    }
    
    return str;
}