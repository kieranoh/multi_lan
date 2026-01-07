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

    // 표현식 정리: 공백 제거
    const cleanedExpr = expr.trim();
    
    // 보안 검증: 허용된 문자만 포함하는지 확인
    // 숫자, 기본 연산자(+, -, *, /), 소수점, 괄호, 공백 허용
    const validPattern = /^[\d+\-*/().\s]+$/;
    if (!validPattern.test(cleanedExpr)) {
        return '';
    }

    // 괄호 짝이 맞는지 확인
    const bracketStack = [];
    for (let i = 0; i < cleanedExpr.length; i++) {
        if (cleanedExpr[i] === '(') {
            bracketStack.push('(');
        } else if (cleanedExpr[i] === ')') {
            if (bracketStack.length === 0) {
                return ''; // 닫는 괄호가 여는 괄호보다 많은 경우
            }
            bracketStack.pop();
        }
    }
    if (bracketStack.length > 0) {
        return ''; // 여는 괄호가 닫는 괄호보다 많은 경우
    }

    try {
        // 안전한 평가를 위해 Function 생성자 사용
        // 이 방법은 eval보다 더 제한적이며 전역 스코프에 접근하지 않음
        const result = new Function(`return ${cleanedExpr}`)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환하여 반환
        return String(result);
    } catch (error) {
        // 평가 중 발생한 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}