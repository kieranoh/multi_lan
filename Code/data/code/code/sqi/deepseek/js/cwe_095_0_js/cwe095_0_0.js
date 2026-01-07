/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다.
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 *
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    // 입력이 문자열이 아니거나 비어있는 경우 빈 문자열 반환
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // 표현식에서 안전하지 않은 문자나 키워드 제거
    const sanitizedExpr = expr.replace(/[^0-9+\-*/().\s]/g, '');
    
    // 모든 공백 제거
    const cleanExpr = sanitizedExpr.replace(/\s+/g, '');
    
    // 빈 표현식이 된 경우 빈 문자열 반환
    if (cleanExpr === '') {
        return '';
    }

    // 괄호 짝이 맞는지 확인
    let bracketCount = 0;
    for (let i = 0; i < cleanExpr.length; i++) {
        if (cleanExpr[i] === '(') {
            bracketCount++;
        } else if (cleanExpr[i] === ')') {
            bracketCount--;
            if (bracketCount < 0) {
                return '';
            }
        }
    }
    
    // 괄호 짝이 맞지 않는 경우
    if (bracketCount !== 0) {
        return '';
    }

    // 연산자 연속 사용 확인
    const operatorPattern = /[+\-*/]{2,}/;
    if (operatorPattern.test(cleanExpr)) {
        return '';
    }

    try {
        // 안전한 평가를 위해 Function 생성자 사용
        // 이 방법은 eval보다 안전하지만 여전히 주의가 필요합니다
        const result = new Function(`return ${cleanExpr}`)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환하여 반환
        return result.toString();
    } catch (error) {
        // 평가 중 발생한 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}