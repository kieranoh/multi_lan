/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다.
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 * 
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    // 빈 문자열이나 null/undefined 체크
    if (!expr || typeof expr !== 'string') {
        return '';
    }
    
    // 공백 제거
    const trimmedExpr = expr.trim();
    if (trimmedExpr === '') {
        return '';
    }
    
    try {
        // 안전한 평가를 위한 검증
        // 1. 허용된 문자만 있는지 확인 (숫자, 연산자, 공백, 괄호, 소수점)
        const allowedChars = /^[\d+\-*/().\s]+$/;
        if (!allowedChars.test(trimmedExpr)) {
            return '';
        }
        
        // 2. 괄호 짝이 맞는지 확인
        let bracketCount = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                bracketCount++;
            } else if (trimmedExpr[i] === ')') {
                bracketCount--;
                if (bracketCount < 0) {
                    return '';
                }
            }
        }
        if (bracketCount !== 0) {
            return '';
        }
        
        // 3. 연산자 위치 검증
        const operatorPattern = /[+\-*/]/g;
        const operators = trimmedExpr.match(operatorPattern);
        if (operators) {
            // 연산자가 연속으로 나오는지 확인 (단, 음수 기호는 예외)
            const invalidOperatorSequence = /[+\-*/]{2,}/;
            if (invalidOperatorSequence.test(trimmedExpr.replace(/\s+/g, ''))) {
                // 음수 기호는 허용 (예: 5 * -3, (-2 + 3))
                // 하지만 연산자 뒤에 바로 음수 기호가 오는 경우는 허용
                const cleanedExpr = trimmedExpr.replace(/\s+/g, '');
                for (let i = 0; i < cleanedExpr.length - 1; i++) {
                    if ('+-*/'.includes(cleanedExpr[i]) && '*/'.includes(cleanedExpr[i + 1])) {
                        return '';
                    }
                }
            }
        }
        
        // 4. eval 사용 전 추가 검증
        // a. 숫자로 시작하거나 '('로 시작해야 함
        const firstChar = trimmedExpr.replace(/\s+/g, '')[0];
        if (!'0123456789('.includes(firstChar) && firstChar !== '-') {
            return '';
        }
        
        // b. 숫자로 끝나거나 ')'로 끝나야 함
        const lastChar = trimmedExpr.replace(/\s+/g, '').slice(-1);
        if (!'0123456789)'.includes(lastChar)) {
            return '';
        }
        
        // 5. 안전한 평가 수행
        // Function 생성자를 사용하여 전역 범위에 접근하지 않도록 함
        const result = new Function(`return ${trimmedExpr}`)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (소수점 처리)
        const strResult = result.toString();
        
        // 소수점 이하 불필요한 0 제거
        if (strResult.includes('.')) {
            return parseFloat(result.toFixed(10)).toString();
        }
        
        return strResult;
        
    } catch (error) {
        // 모든 오류 발생 시 빈 문자열 반환
        return '';
    }
}