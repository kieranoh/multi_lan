/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다.
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 *
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    // 입력 유효성 검사
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // 표현식 정리
    const cleanedExpr = expr.trim();
    
    // 보안 검사: 허용된 문자만 포함하는지 확인
    // 숫자, 기본 연산자(+, -, *, /, %), 괄호, 공백, 소수점만 허용
    const allowedChars = /^[\d+\-*/().%\s]+$/;
    if (!allowedChars.test(cleanedExpr)) {
        return '';
    }

    // 괄호 짝이 맞는지 확인
    const parenthesesCheck = (expr) => {
        let balance = 0;
        for (let i = 0; i < expr.length; i++) {
            if (expr[i] === '(') balance++;
            if (expr[i] === ')') balance--;
            if (balance < 0) return false; // 닫는 괄호가 먼저 나옴
        }
        return balance === 0;
    };

    if (!parenthesesCheck(cleanedExpr)) {
        return '';
    }

    // 연산자 우선순위 정의
    const precedence = {
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2,
        '%': 2
    };

    // 중위 표현식을 후위 표현식으로 변환 (Shunting-yard 알고리즘)
    const infixToPostfix = (expression) => {
        const output = [];
        const operators = [];
        
        // 토큰 분리
        const tokens = expression.match(/(\d+(?:\.\d+)?|[+\-*/%()])/g) || [];
        
        for (let token of tokens) {
            // 숫자인 경우
            if (!isNaN(parseFloat(token))) {
                output.push(parseFloat(token));
            }
            // 연산자인 경우
            else if (token in precedence) {
                while (operators.length > 0 && 
                       operators[operators.length - 1] !== '(' &&
                       precedence[operators[operators.length - 1]] >= precedence[token]) {
                    output.push(operators.pop());
                }
                operators.push(token);
            }
            // 여는 괄호인 경우
            else if (token === '(') {
                operators.push(token);
            }
            // 닫는 괄호인 경우
            else if (token === ')') {
                while (operators.length > 0 && operators[operators.length - 1] !== '(') {
                    output.push(operators.pop());
                }
                operators.pop(); // '(' 제거
            }
        }
        
        // 남은 연산자 처리
        while (operators.length > 0) {
            output.push(operators.pop());
        }
        
        return output;
    };

    // 후위 표현식 계산
    const evaluatePostfix = (postfix) => {
        const stack = [];
        
        for (let token of postfix) {
            // 숫자인 경우
            if (typeof token === 'number') {
                stack.push(token);
            }
            // 연산자인 경우
            else {
                if (stack.length < 2) {
                    throw new Error('Invalid expression');
                }
                
                const b = stack.pop();
                const a = stack.pop();
                
                switch (token) {
                    case '+':
                        stack.push(a + b);
                        break;
                    case '-':
                        stack.push(a - b);
                        break;
                    case '*':
                        stack.push(a * b);
                        break;
                    case '/':
                        if (b === 0) {
                            throw new Error('Division by zero');
                        }
                        stack.push(a / b);
                        break;
                    case '%':
                        if (b === 0) {
                            throw new Error('Modulo by zero');
                        }
                        stack.push(a % b);
                        break;
                    default:
                        throw new Error('Unknown operator');
                }
            }
        }
        
        if (stack.length !== 1) {
            throw new Error('Invalid expression');
        }
        
        return stack[0];
    };

    try {
        // 후위 표현식으로 변환
        const postfix = infixToPostfix(cleanedExpr);
        
        // 후위 표현식 평가
        const result = evaluatePostfix(postfix);
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 정수인 경우 정수로, 소수인 경우 소수점 이하 10자리까지 표시
        const formattedResult = Number.isInteger(result) 
            ? result.toString() 
            : parseFloat(result.toFixed(10)).toString();
        
        return formattedResult;
    } catch (error) {
        // 모든 오류는 빈 문자열 반환
        return '';
    }
}