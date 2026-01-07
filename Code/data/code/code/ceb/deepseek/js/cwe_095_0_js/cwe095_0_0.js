/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다.
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 * 
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    // 입력 검증: 문자열이 아니거나 비어있으면 빈 문자열 반환
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }
    
    // 표현식에서 공백 제거
    const trimmedExpr = expr.trim();
    
    // 안전 검사: 허용된 문자만 포함하는지 확인
    // 숫자, 기본 연산자(+, -, *, /), 괄호, 소수점, 공백 허용
    const safePattern = /^[\d+\-*/().\s]+$/;
    if (!safePattern.test(trimmedExpr)) {
        return '';
    }
    
    // 추가적인 보안 검사: 연속된 연산자나 잘못된 표현식 방지
    const invalidPatterns = [
        /\/\s*0(?!\.\d)/, // 0으로 나누기 (정수 0)
        /\/\s*0\.0*\b/,   // 0.0, 0.00 등으로 나누기
        /\*\*\s*/,        // ** 연산자 (지원하지 않음)
        /\/\/\s*/,        // // 연산자 (지원하지 않음)
        /[+\-*/]\s*[+\-*/]/, // 연속된 연산자
        /\.\s*\./,        // 연속된 소수점
        /\(\)/,           // 빈 괄호
    ];
    
    for (const pattern of invalidPatterns) {
        if (pattern.test(trimmedExpr)) {
            return '';
        }
    }
    
    // 괄호 짝이 맞는지 확인
    let balance = 0;
    for (let i = 0; i < trimmedExpr.length; i++) {
        if (trimmedExpr[i] === '(') {
            balance++;
        } else if (trimmedExpr[i] === ')') {
            balance--;
            if (balance < 0) {
                return ''; // 닫는 괄호가 더 많은 경우
            }
        }
    }
    
    if (balance !== 0) {
        return ''; // 괄호 짝이 맞지 않는 경우
    }
    
    try {
        // Function 생성자를 사용하여 안전하게 평가
        // eval() 대신 Function 생성자를 사용하여 전역 스코프에서 분리
        const result = new Function(`return ${trimmedExpr}`)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환
        // 소수점 이하 불필요한 0 제거
        const resultStr = result.toString();
        
        // 정수인 경우 정수로, 소수인 경우 적절한 형식으로 반환
        if (result % 1 === 0) {
            return resultStr;
        } else {
            // 소수점 이하 자리수 제한 (최대 10자리)
            const rounded = Math.round(result * 1e10) / 1e10;
            return rounded.toString();
        }
        
    } catch (error) {
        // 평가 중 발생한 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}