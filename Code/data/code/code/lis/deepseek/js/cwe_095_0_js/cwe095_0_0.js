function evaluate_expression(expr) {
    // 입력 유효성 검사
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // 안전한 문자 패턴: 숫자, 기본 연산자, 공백, 소수점, 괄호
    const safePattern = /^[\d+\-*/().\s]+$/;
    if (!safePattern.test(expr)) {
        return '';
    }

    // 잠재적인 위험한 패턴 필터링
    const dangerousPatterns = [
        /\.\./,        // 연속된 점
        /\/\//,        // 이중 슬래시
        /[+\-*/]{2,}/, // 연속된 연산자
        /\(\)/,        // 빈 괄호
        /[+\-*/.]$/,   // 표현식이 연산자나 점으로 끝남
        /^[+\-*/.]/,   // 표현식이 연산자나 점으로 시작함
        /[+\-*/]{2,}/  // 연속된 연산자
    ];

    for (const pattern of dangerousPatterns) {
        if (pattern.test(expr.replace(/\s/g, ''))) {
            return '';
        }
    }

    try {
        // 공백 제거
        const cleanedExpr = expr.replace(/\s/g, '');
        
        // 괄호 균형 확인
        let balance = 0;
        for (let i = 0; i < cleanedExpr.length; i++) {
            if (cleanedExpr[i] === '(') balance++;
            if (cleanedExpr[i] === ')') balance--;
            if (balance < 0) return ''; // 닫는 괄호가 더 많음
        }
        if (balance !== 0) return ''; // 괄호가 균형이 맞지 않음

        // 안전한 평가를 위한 함수
        const safeEval = (expression) => {
            // 연산자 우선순위를 고려한 계산
            const calculate = (a, op, b) => {
                a = parseFloat(a);
                b = parseFloat(b);
                
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

            // 연산자 우선순위 정의
            const precedence = {
                '+': 1,
                '-': 1,
                '*': 2,
                '/': 2
            };

            // 토큰화
            const tokens = expression.match(/(\d+(?:\.\d+)?)|[+\-*/()]/g);
            if (!tokens) return '';

            // 중위 표기법을 후위 표기법으로 변환 (Shunting-yard 알고리즘)
            const output = [];
            const operators = [];

            for (const token of tokens) {
                if (!isNaN(parseFloat(token))) {
                    output.push(parseFloat(token));
                } else if (token in precedence) {
                    while (operators.length > 0 && 
                           operators[operators.length - 1] !== '(' &&
                           precedence[operators[operators.length - 1]] >= precedence[token]) {
                        output.push(operators.pop());
                    }
                    operators.push(token);
                } else if (token === '(') {
                    operators.push(token);
                } else if (token === ')') {
                    while (operators.length > 0 && operators[operators.length - 1] !== '(') {
                        output.push(operators.pop());
                    }
                    if (operators.pop() !== '(') {
                        throw new Error('Mismatched parentheses');
                    }
                }
            }

            while (operators.length > 0) {
                const op = operators.pop();
                if (op === '(' || op === ')') {
                    throw new Error('Mismatched parentheses');
                }
                output.push(op);
            }

            // 후위 표기법 평가
            const stack = [];
            for (const token of output) {
                if (typeof token === 'number') {
                    stack.push(token);
                } else {
                    if (stack.length < 2) {
                        throw new Error('Invalid expression');
                    }
                    const b = stack.pop();
                    const a = stack.pop();
                    stack.push(calculate(a, token, b));
                }
            }

            if (stack.length !== 1) {
                throw new Error('Invalid expression');
            }

            return stack[0];
        };

        const result = safeEval(cleanedExpr);
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result) || isNaN(result)) {
            return '';
        }

        // 결과를 문자열로 변환 (불필요한 소수점 제거)
        const resultStr = result.toString();
        return resultStr.includes('.') ? parseFloat(result.toFixed(10)).toString() : resultStr;
        
    } catch (error) {
        // 모든 오류는 빈 문자열 반환
        return '';
    }
}