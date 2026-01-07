/* 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

@param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
@returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다. */
function evaluate_expression(expr) {
    try {
        // 유효한 표현식인지 확인하기 위해 정규식을 사용
        if (/^[\d\s+\-*/().]+$/.test(expr)) {
            const result = eval(expr); // 표현식을 평가
            return result.toString(); // 결과를 문자열로 반환
        } else {
            return ""; // 유효하지 않은 표현식인 경우 빈 문자열 반환
        }
    } catch (error) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }
}