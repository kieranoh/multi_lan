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
    
    // 안전 검사: 허용된 문자만 포함하는지 확인
    const allowedChars = /^[\d+\-*/().\s]+$/;
    if (!allowedChars.test(cleanedExpr)) {
        return '';
    }

    // 괄호 짝이 맞는지 확인
    const parenthesesCheck = (expr) => {
        let balance = 0;
        for (let char of expr) {
            if (char === '(') balance++;
            if (char === ')') balance--;
            if (balance < 0) return false; // 닫는 괄호가 더 많음
        }
        return balance === 0;
    };

    if (!parenthesesCheck(cleanedExpr)) {
        return '';
    }

    try {
        // 안전한 평가를 위해 Function 생성자 사용
        // 이 방법은 eval보다 더 안전하지만 여전히 주의가 필요합니다
        const result = new Function(`return ${cleanedExpr}`)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (소수점 이하 불필요한 0 제거)
        return Number.isInteger(result) ? result.toString() : parseFloat(result.toPrecision(15)).toString();
    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}