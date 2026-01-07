/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다.
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 * 
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    try {
        // 입력 검증: 빈 문자열 또는 null/undefined 체크
        if (!expr || typeof expr !== 'string') {
            return '';
        }
        
        // 공백 제거
        const trimmedExpr = expr.trim();
        if (trimmedExpr === '') {
            return '';
        }
        
        // 안전한 문자 패턴 검증: 숫자, 기본 연산자, 괄호, 공백만 허용
        const safePattern = /^[\d+\-*/().\s]+$/;
        if (!safePattern.test(trimmedExpr)) {
            return '';
        }
        
        // 잠재적인 위험한 패턴 검증
        const dangerousPatterns = [
            /eval\(/i,
            /Function\(/i,
            /setTimeout\(/i,
            /setInterval\(/i,
            /\.constructor\(/i,
            /import\(/i,
            /require\(/i,
            /process\./i,
            /document\./i,
            /window\./i,
            /globalThis\./i
        ];
        
        for (const pattern of dangerousPatterns) {
            if (pattern.test(trimmedExpr)) {
                return '';
            }
        }
        
        // 괄호 짝 검증
        const parenthesesStack = [];
        for (let i = 0; i < trimmedExpr.length; i++) {
            const char = trimmedExpr[i];
            if (char === '(') {
                parenthesesStack.push('(');
            } else if (char === ')') {
                if (parenthesesStack.length === 0) {
                    return ''; // 닫는 괄호가 여는 괄호보다 많음
                }
                parenthesesStack.pop();
            }
        }
        
        if (parenthesesStack.length > 0) {
            return ''; // 여는 괄호가 닫는 괄호보다 많음
        }
        
        // 연산자 연속 사용 검증
        const operatorPattern = /[+\-*/]{2,}/;
        if (operatorPattern.test(trimmedExpr)) {
            return '';
        }
        
        // 소수점 검증: 연속된 소수점이나 잘못된 소수점 위치
        const decimalPattern = /\.\d*\./;
        if (decimalPattern.test(trimmedExpr)) {
            return '';
        }
        
        // 표현식 평가
        // Function 생성자를 사용하는 대신 안전한 평가 방법 사용
        const sanitizedExpr = trimmedExpr.replace(/\s+/g, '');
        
        // 빈 표현식 검증
        if (sanitizedExpr === '') {
            return '';
        }
        
        // 나누기 0 검증
        if (sanitizedExpr.includes('/0') && !sanitizedExpr.includes('/0.')) {
            // 0으로 나누기 시도, 하지만 0.0은 허용
            const dividedByZeroPattern = /\/0(?!\.)/;
            if (dividedByZeroPattern.test(sanitizedExpr)) {
                return '';
            }
        }
        
        // 안전한 평가를 위한 함수
        const safeEval = (expression) => {
            // 연산자 우선순위 처리를 위한 함수
            const evaluate = (tokens) => {
                const values = [];
                const ops = [];
                
                const precedence = {
                    '+': 1,
                    '-': 1,
                    '*': 2,
                    '/': 2
                };
                
                const applyOp = (op, b, a) => {
                    switch (op) {
                        case '+': return a + b;
                        case '-': return a - b;
                        case '*': return a * b;
                        case '/': 
                            if (b === 0) throw new Error('Division by zero');
                            return a / b;
                        default: throw new Error('Invalid operator');
                    }
                };
                
                for (let i = 0; i < tokens.length; i++) {
                    const token = tokens[i];
                    
                    if (!isNaN(token) && token !== '') {
                        values.push(parseFloat(token));
                    } else if (token === '(') {
                        ops.push(token);
                    } else if (token === ')') {
                        while (ops.length && ops[ops.length - 1] !== '(') {
                            values.push(applyOp(ops.pop(), values.pop(), values.pop()));
                        }
                        ops.pop(); // '(' 제거
                    } else if (precedence[token]) {
                        while (ops.length && precedence[ops[ops.length - 1]] >= precedence[token]) {
                            values.push(applyOp(ops.pop(), values.pop(), values.pop()));
                        }
                        ops.push(token);
                    }
                }
                
                while (ops.length) {
                    values.push(applyOp(ops.pop(), values.pop(), values.pop()));
                }
                
                return values.length > 0 ? values.pop() : 0;
            };
            
            // 토큰화
            const tokenize = (expr) => {
                const tokens = [];
                let currentNumber = '';
                
                for (let i = 0; i < expr.length; i++) {
                    const char = expr[i];
                    
                    if (!isNaN(char) || char === '.') {
                        currentNumber += char;
                    } else {
                        if (currentNumber !== '') {
                            tokens.push(currentNumber);
                            currentNumber = '';
                        }
                        
                        if (char === '-' && (i === 0 || expr[i-1] === '(' || ['+', '-', '*', '/'].includes(expr[i-1]))) {
                            // 음수 처리
                            currentNumber += char;
                        } else if (['+', '-', '*', '/', '(', ')'].includes(char)) {
                            tokens.push(char);
                        }
                    }
                }
                
                if (currentNumber !== '') {
                    tokens.push(currentNumber);
                }
                
                return tokens;
            };
            
            const tokens = tokenize(expression);
            return evaluate(tokens);
        };
        
        const result = safeEval(sanitizedExpr);
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (불필요한 소수점 제거)
        const resultStr = Number.isInteger(result) ? 
            result.toString() : 
            parseFloat(result.toFixed(10)).toString();
        
        return resultStr;
        
    } catch (error) {
        // 모든 오류를 잡아 빈 문자열 반환
        return '';
    }
}