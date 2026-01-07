/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다.
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 * 
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    try {
        // 입력 유효성 검사
        if (typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }

        // 표현식 정리
        const cleanedExpr = expr.trim();
        
        // 보안 검증: 허용된 문자만 포함하는지 확인
        // 숫자, 기본 연산자(+, -, *, /), 소수점, 괄호, 공백만 허용
        const validPattern = /^[\d+\-*/().\s]+$/;
        if (!validPattern.test(cleanedExpr)) {
            return '';
        }

        // 괄호 짝 검증
        const parenthesesStack = [];
        for (let i = 0; i < cleanedExpr.length; i++) {
            const char = cleanedExpr[i];
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

        // 빈 괄호 검증
        if (/\(\)/.test(cleanedExpr)) {
            return '';
        }

        // 연산자 위치 검증
        // 시작이나 끝이 연산자인 경우 (단, 음수는 허용)
        if (/^[*/+]/.test(cleanedExpr) || /[+\-*/]$/.test(cleanedExpr)) {
            return '';
        }

        // 연속된 연산자 검증
        if (/[+\-*/]{2,}/.test(cleanedExpr.replace(/\s+/g, ''))) {
            return '';
        }

        // 0으로 나누기 검증
        if (/\/\s*0(?!\.)/.test(cleanedExpr.replace(/\s+/g, ''))) {
            return '';
        }

        // 소수점 검증
        if (/\.\d*\./.test(cleanedExpr) || /\d+\.\d+\./.test(cleanedExpr)) {
            return '';
        }

        // 안전한 평가를 위해 Function 생성자 사용
        // eval() 대신 Function 생성자를 사용하여 전역 스코프에서 평가
        const result = new Function(`return ${cleanedExpr}`)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }

        // 결과 형식화
        // 소수점 이하 10자리까지 표시하되, 불필요한 0 제거
        const formattedResult = parseFloat(result.toFixed(10)).toString();
        
        return formattedResult;

    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}