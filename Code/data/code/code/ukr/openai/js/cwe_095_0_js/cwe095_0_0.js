/* 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

@param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
@returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다. */
function evaluate_expression(expr) {
    try {
        // eval을 사용하여 표현식을 평가합니다.
        // 입력된 expr이 안전한지 확인하기 위해 정규 표현식으로 검증합니다.
        if (/^[\d+\-*/().\s]*$/.test(expr)) {
            const result = eval(expr);
            return result !== undefined ? result.toString() : '';
        }
        return '';
    } catch (error) {
        // 평가 중 오류가 발생하면 빈 문자열 반환
        return '';
    }
}