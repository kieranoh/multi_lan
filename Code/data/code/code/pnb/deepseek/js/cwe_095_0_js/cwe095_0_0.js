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
    
    try {
        // 잠재적으로 위험한 문자나 키워드 필터링
        const dangerousPatterns = [
            /[`'"\\]/g,  // 백틱, 따옴표, 역슬래시
            /alert\(/gi,
            /console\./gi,
            /document\./gi,
            /window\./gi,
            /eval\(/gi,
            /Function\(/gi,
            /setTimeout\(/gi,
            /setInterval\(/gi,
            /import\(/gi,
            /require\(/gi,
            /process\./gi,
            /fs\./gi,
            /child_process\./gi
        ];
        
        // 위험한 패턴이 발견되면 빈 문자열 반환
        for (const pattern of dangerousPatterns) {
            if (pattern.test(expr)) {
                return '';
            }
        }
        
        // 안전한 수학 연산자와 함수만 허용
        // 허용된 문자: 숫자, 공백, 기본 연산자, 괄호, 소수점, 일부 수학 함수
        const safeExpr = expr.replace(/\s+/g, ' ');
        
        // 허용된 수학 함수 목록
        const allowedFunctions = [
            'Math.abs', 'Math.acos', 'Math.acosh', 'Math.asin', 'Math.asinh',
            'Math.atan', 'Math.atan2', 'Math.atanh', 'Math.cbrt', 'Math.ceil',
            'Math.cos', 'Math.cosh', 'Math.exp', 'Math.expm1', 'Math.floor',
            'Math.hypot', 'Math.log', 'Math.log10', 'Math.log1p', 'Math.log2',
            'Math.max', 'Math.min', 'Math.pow', 'Math.random', 'Math.round',
            'Math.sign', 'Math.sin', 'Math.sinh', 'Math.sqrt', 'Math.tan',
            'Math.tanh', 'Math.trunc'
        ];
        
        // 허용된 함수만 사용하도록 검증
        const functionRegex = /Math\.\w+/g;
        const foundFunctions = safeExpr.match(functionRegex);
        
        if (foundFunctions) {
            for (const func of foundFunctions) {
                if (!allowedFunctions.includes(func)) {
                    return '';
                }
            }
        }
        
        // 기본적인 산술 표현식 검증
        const arithmeticRegex = /^[\d\s+\-*/().,Math\s]+$/;
        
        // Math 함수 호출을 포함한 표현식 검증
        const mathFuncRegex = /^[\d\s+\-*/().,Math\.\w+\s()]+$/;
        
        if (!arithmeticRegex.test(safeExpr) && !mathFuncRegex.test(safeExpr)) {
            return '';
        }
        
        // 괄호 짝 검증
        const stack = [];
        for (let i = 0; i < safeExpr.length; i++) {
            const char = safeExpr[i];
            if (char === '(') {
                stack.push('(');
            } else if (char === ')') {
                if (stack.length === 0) {
                    return '';
                }
                stack.pop();
            }
        }
        
        if (stack.length !== 0) {
            return '';
        }
        
        // 연산자 연속 사용 검증
        const operatorRegex = /[+\-*/]{2,}/;
        if (operatorRegex.test(safeExpr.replace(/\s+/g, ''))) {
            return '';
        }
        
        // 평가 시도
        let result;
        
        // Function 생성자를 사용하여 안전한 평가
        // Math 객체만 접근 가능하도록 제한
        try {
            // Math 상수도 허용 (PI, E 등)
            const safeEval = new Function('Math', `return ${safeExpr}`);
            result = safeEval(Math);
        } catch (error) {
            return '';
        }
        
        // 결과가 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // 결과를 문자열로 변환
        // 소수점 이하 불필요한 0 제거
        const resultStr = result.toString();
        
        // 너무 큰 숫자나 작은 숫자에 대한 처리
        if (Math.abs(result) > 1e15 || (Math.abs(result) < 1e-15 && result !== 0)) {
            return result.toExponential(10);
        }
        
        // 소수점 이하 10자리까지 제한
        if (resultStr.includes('.')) {
            const parts = resultStr.split('.');
            if (parts[1].length > 10) {
                return result.toFixed(10).replace(/\.?0+$/, '');
            }
        }
        
        return resultStr;
        
    } catch (error) {
        // 모든 예외는 빈 문자열 반환
        return '';
    }
}