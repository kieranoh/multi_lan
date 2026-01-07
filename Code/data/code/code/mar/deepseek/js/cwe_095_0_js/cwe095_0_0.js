function evaluate_expression(expr) {
    try {
        // 입력이 문자열인지 확인
        if (typeof expr !== 'string') {
            return '';
        }
        
        // 빈 문자열 또는 공백만 있는 경우 처리
        expr = expr.trim();
        if (expr === '') {
            return '';
        }
        
        // 안전한 산술 표현식인지 검증
        // 허용되는 문자: 숫자, 소수점, 기본 연산자, 공백, 괄호
        const safePattern = /^[\d\s\+\-\*\/\.\(\)]+$/;
        if (!safePattern.test(expr)) {
            return '';
        }
        
        // 연산자 연속 사용 방지 (예: "2++3", "5*/2")
        const operatorPattern = /[\+\-\*\/]{2,}/;
        if (operatorPattern.test(expr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // 소수점 잘못된 사용 방지 (예: "2..3", ".5.2")
        const decimalPattern = /\.\d*\./;
        if (decimalPattern.test(expr)) {
            return '';
        }
        
        // 괄호 짝이 맞는지 확인
        const parentheses = expr.replace(/[^\(\)]/g, '');
        let balance = 0;
        for (let char of parentheses) {
            if (char === '(') balance++;
            else if (char === ')') balance--;
            if (balance < 0) return ''; // 닫는 괄호가 먼저 나온 경우
        }
        if (balance !== 0) return ''; // 괄호 짝이 맞지 않는 경우
        
        // 공백 제거
        expr = expr.replace(/\s+/g, '');
        
        // 나누기 0 방지
        if (expr.includes('/0') && !expr.includes('/0.')) {
            // "/0"이 있지만 "/0."이 아닌 경우 (0.0은 허용)
            return '';
        }
        
        // eval 대신 Function 생성자를 사용하여 더 안전하게 평가
        // 단, 여전히 주의가 필요하므로 위에서 철저한 검증을 수행
        const result = Function(`"use strict"; return (${expr})`)();
        
        // 결과가 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환
        // 소수점 이하 불필요한 0 제거
        let resultStr = result.toString();
        
        // 너무 큰 숫자나 작은 숫자에 대한 처리
        if (Math.abs(result) > 1e15 || (Math.abs(result) < 1e-6 && result !== 0)) {
            resultStr = result.toExponential(6);
        }
        
        return resultStr;
        
    } catch (error) {
        // 모든 오류 발생 시 빈 문자열 반환
        return '';
    }
}