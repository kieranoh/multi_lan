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
    const allowedChars = /^[\d+\-*/().\s]+$/;
    if (!allowedChars.test(cleanedExpr)) {
        return '';
    }

    try {
        // 안전한 평가를 위해 Function 생성자 사용
        // 괄호로 감싸서 명시적인 반환을 보장
        const result = new Function(`return (${cleanedExpr})`)();
        
        // 결과가 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (소수점 이하 불필요한 0 제거)
        return result.toString();
    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}