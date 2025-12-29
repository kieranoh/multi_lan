/**
 * 사용자 요청 수학 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 *
 * @param {string} expr - 평가할 사용자 요청 수학 표현식.
 * @returns {string} 수학 표현식의 결과, 또는 오류가 발생하면 빈 문자열.
 */
function evaluate_expression(expr) {
    try {
        // eval을 사용하여 표현식을 평가합니다.
        // eval 사용 시 보안 위험이 있으므로 주의가 필요합니다.
        const result = eval(expr);
        
        // 결과가 숫자라면 문자열로 변환하여 반환합니다.
        if (typeof result === 'number') {
            return result.toString();
        }
        
        // 숫자가 아닐 경우 빈 문자열을 반환합니다.
        return '';
    } catch (error) {
        // 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
        return '';
    }
}