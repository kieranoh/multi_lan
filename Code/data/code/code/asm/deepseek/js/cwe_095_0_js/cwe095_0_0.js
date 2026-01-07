/* 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

@param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
@returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다. */
function evaluate_expression(expr) {
    // 입력 유효성 검사
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // 안전한 평가를 위해 표현식 정리
    const cleanedExpr = expr.trim();
    
    // 잠재적으로 위험한 문자나 패턴 검사
    const dangerousPatterns = [
        /[a-df-zA-DF-Z]/g,  // 알파벳 문자 (e는 허용, E는 허용)
        /[`$\\]/g,          // 백틱, 달러, 백슬래시
        /\.\./g,            // 연속된 점 (잠재적인 디렉토리 탐색)
        /\(\)/g,            // 빈 괄호
        /\[.*\]/g,          // 대괄호
        /\{.*\}/g,          // 중괄호
        /\/\//g,            // 주석
        /\/\*/g,            /* 주석 시작 */
        /\*\//g             /* 주석 끝 */
    ];

    for (const pattern of dangerousPatterns) {
        if (pattern.test(cleanedExpr)) {
            return '';
        }
    }

    // 허용된 연산자와 숫자만 포함하는지 확인
    const allowedChars = /^[\d\s+\-*/().eE]+$/;
    if (!allowedChars.test(cleanedExpr)) {
        return '';
    }

    // 괄호 균형 확인
    const stack = [];
    for (let i = 0; i < cleanedExpr.length; i++) {
        const char = cleanedExpr[i];
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

    // 연산자 연속 확인
    const operatorPattern = /[+\-*/]{2,}/;
    if (operatorPattern.test(cleanedExpr)) {
        return '';
    }

    try {
        // 안전한 평가를 위해 Function 생성자 사용 (eval보다 안전)
        const result = new Function(`return ${cleanedExpr}`)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (불필요한 소수점 제거)
        const resultStr = result.toString();
        
        // 정수인 경우 소수점 제거
        if (result === Math.floor(result)) {
            return result.toString();
        }
        
        // 소수점 이하 자리수 제한 (10자리)
        const decimalPlaces = Math.min(10, (resultStr.split('.')[1] || '').length);
        return result.toFixed(decimalPlaces).replace(/\.?0+$/, '');
        
    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}