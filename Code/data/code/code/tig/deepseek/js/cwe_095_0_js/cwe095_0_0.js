/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 * 
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    // 입력 검증: 문자열이 아니거나 비어있는 경우
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }
    
    // 표현식 정리: 공백 제거
    const cleanedExpr = expr.trim();
    
    // 보안 검증: 허용된 문자만 포함하는지 확인
    // 허용: 숫자, 소수점, 기본 연산자(+, -, *, /), 괄호, 공백
    const allowedChars = /^[\d+\-*/().\s]+$/;
    if (!allowedChars.test(cleanedExpr)) {
        return '';
    }
    
    // 괄호 균형 검사
    let balance = 0;
    for (let i = 0; i < cleanedExpr.length; i++) {
        if (cleanedExpr[i] === '(') {
            balance++;
        } else if (cleanedExpr[i] === ')') {
            balance--;
            if (balance < 0) {
                return ''; // 닫는 괄호가 여는 괄호보다 먼저 나옴
            }
        }
    }
    if (balance !== 0) {
        return ''; // 괄호가 짝이 맞지 않음
    }
    
    // 빈 괄호 쌍 검사
    if (/\(\)/.test(cleanedExpr)) {
        return '';
    }
    
    try {
        // 안전한 평가를 위한 함수
        const safeEval = (expression) => {
            // 연산자 우선순위를 고려한 평가를 위해 괄호로 감싸고 평가
            // Function 생성자를 사용하여 평가 (보안 주의: 이미 문자 검증 완료)
            return Function(`'use strict'; return (${expression})`)();
        };
        
        const result = safeEval(cleanedExpr);
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (불필요한 소수점 제거)
        const resultStr = result.toString();
        
        // 정수인 경우 소수점 없이, 실수인 경우 적절히 표시
        if (result % 1 === 0) {
            return resultStr;
        } else {
            // 소수점 이하 불필요한 0 제거
            return parseFloat(result.toFixed(10)).toString();
        }
    } catch (error) {
        // 평가 중 발생한 모든 오류는 빈 문자열 반환
        return '';
    }
}