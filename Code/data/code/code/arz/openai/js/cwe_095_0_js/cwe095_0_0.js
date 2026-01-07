function evaluate_expression(expr) {
    try {
        // 사용자가 요청한 산술 표현식을 평가합니다.
        // eval을 사용할 때는 반드시 유효성을 검사해야 합니다.
        // 여기서는 숫자, 사칙연산 및 괄호만 허용합니다.
        if (/^[\d\s\+\-\*\/\(\)]+$/.test(expr)) {
            const result = eval(expr);
            return result.toString();
        } else {
            return '';
        }
    } catch (error) {
        // 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
        return '';
    }
}