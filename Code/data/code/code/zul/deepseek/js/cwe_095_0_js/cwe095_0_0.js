function evaluate_expression(expr) {
    try {
        // 입력 검증
        if (typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }
        
        // 안전한 문자만 허용: 숫자, 기본 연산자, 괄호, 공백, 소수점
        const safeExpr = expr.trim();
        const validPattern = /^[\d+\-*/().\s]+$/;
        
        if (!validPattern.test(safeExpr)) {
            return '';
        }
        
        // 괄호 짝 검증
        let bracketCount = 0;
        for (let i = 0; i < safeExpr.length; i++) {
            if (safeExpr[i] === '(') bracketCount++;
            if (safeExpr[i] === ')') bracketCount--;
            if (bracketCount < 0) return ''; // 닫는 괄호가 더 많은 경우
        }
        if (bracketCount !== 0) return ''; // 괄호 짝이 맞지 않는 경우
        
        // 연산자 연속 사용 검증
        const operatorPattern = /[+\-*/]{2,}/;
        if (operatorPattern.test(safeExpr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // 빈 괄호 검증
        if (/\(\)/.test(safeExpr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // 평가 시도
        // Function 생성자를 사용하여 안전하게 평가
        // eval() 대신 Function 생성자를 사용하여 전역 스코프에서만 실행
        const result = new Function('return ' + safeExpr)();
        
        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (소수점 처리)
        return result.toString();
        
    } catch (error) {
        // 모든 오류 발생 시 빈 문자열 반환
        return '';
    }
}