/**
 * 사용자가 요청한 산술 표현식을 평가하고 결과를 반환합니다.
 * 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 * 
 * @param {string} expr - 평가할 사용자 요청 산술 표현식입니다.
 * @returns {string} 산술 표현식의 결과 또는 오류가 발생하면 빈 문자열입니다.
 */
function evaluate_expression(expr) {
    // 빈 문자열이나 null/undefined 체크
    if (!expr || typeof expr !== 'string') {
        return '';
    }
    
    // 문자열 양쪽의 공백 제거
    expr = expr.trim();
    
    // 빈 문자열이면 빈 문자열 반환
    if (expr === '') {
        return '';
    }
    
    try {
        // 안전한 평가를 위해 사용자 입력 검증
        // 허용된 문자: 숫자, 소수점, 기본 연산자, 괄호, 공백
        const allowedChars = /^[\d+\-*/().\s]+$/;
        
        // 허용되지 않는 문자나 패턴 검사
        if (!allowedChars.test(expr)) {
            return '';
        }
        
        // 잠재적으로 위험한 패턴 검사
        const dangerousPatterns = [
            /eval\(/i,
            /Function\(/i,
            /setTimeout\(/i,
            /setInterval\(/i,
            /new Function\(/i,
            /\.constructor\(/i,
            /import\(/i,
            /require\(/i,
            /process\./i,
            /window\./i,
            /document\./i,
            /alert\(/i,
            /console\./i
        ];
        
        for (const pattern of dangerousPatterns) {
            if (pattern.test(expr)) {
                return '';
            }
        }
        
        // 괄호 짝이 맞는지 확인
        let bracketCount = 0;
        for (let i = 0; i < expr.length; i++) {
            if (expr[i] === '(') {
                bracketCount++;
            } else if (expr[i] === ')') {
                bracketCount--;
                if (bracketCount < 0) {
                    return ''; // 닫는 괄호가 더 많음
                }
            }
        }
        
        if (bracketCount !== 0) {
            return ''; // 괄호 짝이 맞지 않음
        }
        
        // 연산자 연속 사용 체크 (예: "2++3", "5*/2")
        const operatorPattern = /[+\-*/]{2,}/;
        if (operatorPattern.test(expr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // 소수점 잘못된 사용 체크 (예: "2..3", ".5.2")
        const decimalPattern = /\.\d*\./;
        if (decimalPattern.test(expr)) {
            return '';
        }
        
        // 빈 괄호 체크
        if (/\(\)/.test(expr)) {
            return '';
        }
        
        // 안전한 평가를 위해 Function 생성자 사용 (eval보다 안전함)
        // 먼저 표현식에서 모든 공백 제거
        const cleanExpr = expr.replace(/\s+/g, '');
        
        // 표현식이 숫자로만 구성되어 있는지 확인
        if (/^\d+(\.\d+)?$/.test(cleanExpr)) {
            return cleanExpr;
        }
        
        // 안전한 평가 수행
        const result = Function('"use strict"; return (' + cleanExpr + ')')();
        
        // 결과가 숫자인지 확인
        if (typeof result !== 'number' || isNaN(result) || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (소수점 이하 불필요한 0 제거)
        return Number.isInteger(result) ? result.toString() : parseFloat(result.toFixed(10)).toString();
        
    } catch (error) {
        // 모든 오류 발생 시 빈 문자열 반환
        return '';
    }
}