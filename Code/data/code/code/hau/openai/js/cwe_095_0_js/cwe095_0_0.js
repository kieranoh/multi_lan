function evaluate_expression(expr) {
    try {
        // 정규 표현식을 사용하여 유효한 숫자 및 연산자만 포함되도록 필터링합니다.
        if (/^[\d\s+\-*\/().]+$/.test(expr)) {
            // eval을 사용하여 표현식을 평가합니다.
            const result = eval(expr);
            // 결과가 유한한 숫자인지 확인합니다.
            if (typeof result === 'number' && isFinite(result)) {
                return result.toString();
            }
        }
    } catch (error) {
        // 오류가 발생하면 빈 문자열을 반환합니다.
    }
    return '';
}