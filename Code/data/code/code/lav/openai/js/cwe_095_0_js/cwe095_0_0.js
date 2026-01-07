/*
 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.

 @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다. 
*/
function evaluate_expression(expr) {
    try {
        // eval 함수 사용하여 표현식을 평가, 안전성을 위해 제한합니다.
        const result = Function('"use strict";return (' + expr + ')')();
        return result !== undefined ? String(result) : "";
    } catch (error) {
        return "";
    }
}