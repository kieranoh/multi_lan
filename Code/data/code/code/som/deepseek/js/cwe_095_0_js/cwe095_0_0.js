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
    
    // 안전 검사: 허용된 문자만 포함하는지 확인
    // 숫자, 기본 연산자(+, -, *, /), 소수점, 괄호, 공백만 허용
    const safePattern = /^[\d+\-*/().\s]+$/;
    if (!safePattern.test(cleanedExpr)) {
        return '';
    }

    // 잠재적인 위험한 패턴 검사
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
        if (pattern.test(cleanedExpr)) {
            return '';
        }
    }

    try {
        // 괄호 짝이 맞는지 확인
        const parenthesesStack = [];
        for (const char of cleanedExpr) {
            if (char === '(') {
                parenthesesStack.push('(');
            } else if (char === ')') {
                if (parenthesesStack.length === 0) {
                    return '';
                }
                parenthesesStack.pop();
            }
        }
        
        if (parenthesesStack.length !== 0) {
            return '';
        }

        // 연산자 연속 사용 검사
        const operatorPattern = /[+\-*/]{2,}/;
        if (operatorPattern.test(cleanedExpr.replace(/\s+/g, ''))) {
            return '';
        }

        // 빈 괄호 검사
        if (/\(\)/.test(cleanedExpr)) {
            return '';
        }

        // 안전한 평가를 위해 Function 생성자 사용
        // 엄격한 범위 내에서만 평가
        const safeEval = new Function('return (' + cleanedExpr + ')');
        const result = safeEval();

        // 결과가 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }

        // 결과를 문자열로 변환
        // 소수점 이하 불필요한 0 제거
        const resultStr = result.toString();
        
        // 정수인 경우 정수로, 소수인 경우 적절한 형식으로 반환
        if (result % 1 === 0) {
            return resultStr;
        } else {
            // 소수점 이하 최대 10자리까지 표시하지만 불필요한 0은 제거
            return parseFloat(result.toFixed(10)).toString();
        }
        
    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}