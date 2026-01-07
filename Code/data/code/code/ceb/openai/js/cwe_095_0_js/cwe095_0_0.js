/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 *
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    try {
        // eval() 함수를 사용하여 표현식을 평가
        // eval()은 위험할 수 있으므로 실제 애플리케이션에서는 사용을 피해야 함
        const result = eval(expr);
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result === 'number' && !isNaN(result)) {
            return result.toString();
        } else {
            return '';
        }
    } catch (error) {
        // 오류가 발생하면 빈 문자열 반환
        return '';
    }
}