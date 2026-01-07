/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다.
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 *
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    // 입력 검증: expr이 문자열이 아니거나 비어있는 경우 빈 문자열 반환
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // 표현식에서 공백 제거
    const trimmedExpr = expr.replace(/\s+/g, '');
    
    // 보안 검증: 허용된 문자만 포함하는지 확인
    // 허용: 숫자(0-9), 소수점(.), 연산자(+, -, *, /), 괄호((, ))
    const allowedChars = /^[0-9+\-*/().\s]+$/;
    if (!allowedChars.test(trimmedExpr)) {
        return '';
    }

    // 괄호 짝 검증
    let bracketCount = 0;
    for (let i = 0; i < trimmedExpr.length; i++) {
        if (trimmedExpr[i] === '(') {
            bracketCount++;
        } else if (trimmedExpr[i] === ')') {
            bracketCount--;
            if (bracketCount < 0) {
                return ''; // 닫는 괄호가 여는 괄호보다 먼저 나온 경우
            }
        }
    }
    if (bracketCount !== 0) {
        return ''; // 괄호 짝이 맞지 않는 경우
    }

    // 연산자 연속 사용 검증
    const operatorPattern = /[+\-*/]{2,}/;
    if (operatorPattern.test(trimmedExpr)) {
        return '';
    }

    // 소수점 검증: 연속된 소수점이나 숫자 없는 소수점 방지
    const decimalPattern = /\.\d*\./;
    if (decimalPattern.test(trimmedExpr)) {
        return '';
    }

    try {
        // eval() 사용 전 추가 검증
        // 1. 숫자로 시작하거나 '('로 시작하는지 확인
        const firstChar = trimmedExpr[0];
        if (!/[\d(]/.test(firstChar) && firstChar !== '-') {
            return '';
        }

        // 2. 숫자로 끝나거나 ')'로 끝나는지 확인
        const lastChar = trimmedExpr[trimmedExpr.length - 1];
        if (!/[\d)]/.test(lastChar)) {
            return '';
        }

        // 3. 안전한 eval 래퍼 함수
        const safeEval = (expression) => {
            // Function 생성자를 사용하여 전역 스코프에서 평가
            try {
                // 소수점 처리를 위해 parseFloat 사용
                const result = Function(`"use strict"; return (${expression})`)();
                
                // 결과가 유효한 숫자인지 확인
                if (typeof result !== 'number' || !isFinite(result)) {
                    return '';
                }
                
                // 결과 반환 (소수점 이하 불필요한 0 제거)
                return result.toString();
            } catch (error) {
                return '';
            }
        };

        const result = safeEval(trimmedExpr);
        
        // 결과가 빈 문자열이거나 유효하지 않은 경우
        if (result === '' || result === null || result === undefined) {
            return '';
        }
        
        return result;
        
    } catch (error) {
        // 모든 예외 처리
        return '';
    }
}