/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 *
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    try {
        // 사용자 입력을 안전하게 평가하기 위해, eval() 함수 사용
        // 그러나 eval() 사용은 보안에 취약할 수 있으므로, 
        // 허용된 문자 및 연산자만 포함된 문자열인지 확인합니다.
        if (/^[0-9+\-*/().\s]+$/.test(expr)) {
            const result = eval(expr);
            return String(result);
        } else {
            return '';
        }
    } catch (error) {
        return '';
    }
}