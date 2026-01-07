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
        
        // 안전한 산술 연산자만 허용 (+, -, *, /, %, 괄호, 숫자, 공백, 소수점)
        // 잠재적으로 위험한 문자나 함수 호출 제거
        const safePattern = /^[\d+\-*/().%\s]+$/;
        if (!safePattern.test(expr)) {
            return '';
        }
        
        // 연산자 우선순위를 고려한 안전한 평가
        // 1. 괄호 처리
        // 2. 곱하기, 나누기, 나머지
        // 3. 더하기, 빼기
        
        // 간단한 검증: 괄호 짝이 맞는지 확인
        let bracketCount = 0;
        for (let i = 0; i < expr.length; i++) {
            if (expr[i] === '(') {
                bracketCount++;
            } else if (expr[i] === ')') {
                bracketCount--;
                if (bracketCount < 0) {
                    return '';
                }
            }
        }
        if (bracketCount !== 0) {
            return '';
        }
        
        // 연속된 연산자 확인 (예: "2++3" 또는 "5*/2")
        const operatorPattern = /[+\-*/%]{2,}/;
        if (operatorPattern.test(expr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // 빈 괄호 확인
        if (/\(\)/.test(expr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // 안전한 평가를 위해 Function 생성자 대신 eval() 사용
        // 주의: 실제 프로덕션 환경에서는 더 안전한 방법을 고려해야 함
        const result = eval(expr);
        
        // 결과가 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환 (소수점 이하 불필요한 0 제거)
        return Number.isInteger(result) ? result.toString() : parseFloat(result.toPrecision(15)).toString();
        
    } catch (error) {
        // 모든 오류 발생 시 빈 문자열 반환
        return '';
    }
}