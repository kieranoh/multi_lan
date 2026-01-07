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
    // 숫자, 기본 연산자(+, -, *, /), 소수점, 괄호, 공백만 허용
    const safePattern = /^[\d+\-*/().\s]+$/;
    if (!safePattern.test(cleanedExpr)) {
        return '';
    }

    // 추가 보안 검사: 연속된 연산자 방지 및 괄호 균형 확인
    const operatorPattern = /[+\-*/]{2,}/;
    if (operatorPattern.test(cleanedExpr)) {
        return '';
    }

    // 괄호 균형 확인
    let balance = 0;
    for (let i = 0; i < cleanedExpr.length; i++) {
        if (cleanedExpr[i] === '(') balance++;
        if (cleanedExpr[i] === ')') balance--;
        if (balance < 0) return ''; // 닫는 괄호가 더 많음
    }
    if (balance !== 0) return ''; // 괄호가 맞지 않음

    try {
        // 안전한 평가를 위해 Function 생성자 사용
        // 주의: 실제 프로덕션 환경에서는 더 엄격한 파서를 사용해야 함
        const result = new Function(`return ${cleanedExpr}`)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (불필요한 소수점 제거)
        const resultStr = result.toString();
        
        // 정수인 경우 소수점 없이 반환
        if (result % 1 === 0) {
            return resultStr;
        }
        
        // 소수인 경우 최대 10자리까지 반환
        return parseFloat(result.toFixed(10)).toString();
        
    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}