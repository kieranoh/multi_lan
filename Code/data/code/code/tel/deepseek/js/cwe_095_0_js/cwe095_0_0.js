function evaluate_expression(expr) {
    // 입력 유효성 검사
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // 안전한 문자 패턴: 숫자, 기본 연산자, 소수점, 괄호, 공백
    const safePattern = /^[\d+\-*/().\s]+$/;
    if (!safePattern.test(expr)) {
        return '';
    }

    // 잠재적인 위험한 패턴 필터링
    const dangerousPatterns = [
        /\.\./,       // 연속된 소수점
        /\/\//,       // 연속된 나눗셈
        /\*\*/,       // 연속된 곱셈
        /[+\-*/]{2,}/ // 연속된 연산자
    ];

    for (const pattern of dangerousPatterns) {
        if (pattern.test(expr)) {
            return '';
        }
    }

    // 괄호 균형 검사
    let balance = 0;
    for (let i = 0; i < expr.length; i++) {
        if (expr[i] === '(') balance++;
        if (expr[i] === ')') balance--;
        if (balance < 0) return ''; // 닫는 괄호가 먼저 나온 경우
    }
    if (balance !== 0) return ''; // 괄호가 짝이 맞지 않는 경우

    try {
        // 공백 제거
        const cleanedExpr = expr.replace(/\s+/g, '');
        
        // 빈 문자열 확인
        if (cleanedExpr === '') {
            return '';
        }

        // 표현식 평가
        const result = Function('"use strict"; return (' + cleanedExpr + ')')();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }

        // 결과를 문자열로 변환 (불필요한 소수점 제거)
        const resultStr = result.toString();
        
        // 정수인 경우 소수점 없이 반환
        if (result % 1 === 0) {
            return resultStr.split('.')[0];
        }
        
        return resultStr;
    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}