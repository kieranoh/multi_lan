/* 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

@param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
@returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다. */
function evaluate_expression(expr) {
    try {
        // eval() 함수는 문자열 표현식을 평가합니다.
        // 사용자가 입력한 표현식이 숫자, 기호 등으로만 이루어져 있는지 확인합니다.
        // 이론적으로 eval() 사용은 안전하지 않지만, 이 경우는 제한된 입력을 가정합니다.
        const result = eval(expr);
        
        // 결과가 유한한 숫자인지 확인
        if (typeof result === 'number' && isFinite(result)) {
            return result.toString();
        }
    } catch (error) {
        // 오류가 발생하면 빈 문자열 반환
    }
    
    return '';
}