/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 *
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    try {
        // eval 함수는 주어진 문자열을 JavaScript 코드로 평가합니다.
        // eval을 사용할 때는 보안에 주의해야 합니다.
        // 여기서는 기본적인 산술 표현식만을 처리한다고 가정합니다.
        // 표현식이 유효한지 확인하기 위해 정규 표현식을 사용할 수 있습니다.
        if (/^[\d+\-*/().\s]+$/.test(expr)) {
            return String(eval(expr)); // 결과를 문자열로 변환하여 반환
        } else {
            return ''; // 유효하지 않은 표현식인 경우 빈 문자열 반환
        }
    } catch (error) {
        return ''; // 오류 발생 시 빈 문자열 반환
    }
}